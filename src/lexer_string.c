/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:16:30 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/13 16:55:07 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_lexer_string_quote(char *line, size_t *pos, t_list **head);
static void	ms_lexer_string_dquote(char *line, size_t *pos, t_list **head, \
	t_data *data);
static void	ms_lexer_string_dollar(char *line, size_t *pos, t_list **head, \
	t_data *data);
static void	ms_lexer_string_plain(char *line, size_t *pos, t_list **head);

char	*ms_lexer_string(char *line, t_data *data)
{
	size_t		pos;
	t_list		*head;
	char		*expand_str;

	pos = 0;
	head = NULL;
	while (line[pos])
	{
		if (line[pos] == CHRS_QUOTE[2])
			ms_lexer_string_quote(line, &pos, &head);
		else if (line[pos] == CHRS_QUOTE[1])
			ms_lexer_string_dquote(line, &pos, &head, data);
		else if (line[pos] == CHRS_QUOTE[0])
			ms_lexer_string_dollar(line, &pos, &head, data);
		else
			ms_lexer_string_plain(line, &pos, &head);
	}
	if (head == NULL)
		return (NULL);
	expand_str = ms_lexer_string_lst_strjoin(head);
	ft_lstclear(&head, &free);
	return (expand_str);
}

static void	ms_lexer_string_quote(char *line, size_t *pos, t_list **head)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_quoted(&line[*pos]);
	errno = 0;
	if (stride > LEN_QUOTE_CLOSED)
	{
		ms_lexer_string_lstadd_back_substr(head, line, *pos + 1, stride - 2);
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	else if (stride == LEN_QUOTE_CLOSED)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup(STR_EMPTY)));
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	else if (stride == LEN_QUOTE_UNCLOSED)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup(STR_QUOTE)));
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	*pos += stride;
}

static void	ms_lexer_string_dquote(char *line, size_t *pos, t_list **head, \
	t_data *data)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_quoted(&line[*pos]);
	errno = 0;
	if (stride > LEN_QUOTE_CLOSED)
	{
		ft_lstadd_back(head, \
				ms_expand_envvar_dquote(&line[*pos + 1], stride - 2, data));
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	else if (stride == LEN_QUOTE_CLOSED)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup(STR_EMPTY)));
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	else if (stride == LEN_QUOTE_UNCLOSED)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup(STR_DQUOTE)));
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	*pos += stride;
}

static void	ms_lexer_string_dollar(char *line, size_t *pos, t_list **head, \
	t_data *data)
{
	errno = 0;
	ft_lstadd_back(head, \
			ms_expand_envvar(line, pos, ft_strlen(&line[*pos]), data));
	if (errno == ENOMEM)
		exit(EXIT_FAILURE);
}

static void	ms_lexer_string_plain(char *line, size_t *pos, t_list **head)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_plain(&line[*pos]);
	if (stride > 0)
	{
		errno = 0;
		ms_lexer_string_lstadd_back_substr(head, line, *pos, stride);
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	*pos += stride;
}
