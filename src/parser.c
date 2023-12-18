/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:23:12 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/10 14:57:03 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_until_pipe(t_token *token, size_t idx);
static t_cmd	*make_cmd_list(t_token *token, size_t idx, \
			t_cmd *now, t_data *data);
static bool		ms_parser_chktokenflag(t_token *token);

t_cmd	*parser(t_token *token, t_data *data)
{
	size_t	idx;
	t_cmd	*head;
	t_cmd	*now;

	if (!ms_parser_chktokenflag(token))
		return (print_err_set_status_return_null(MSG_SYNTAX_ERR, 258, data));
	idx = 0;
	head = ms_parser_cmdnew(token, &idx, data);
	if (head == NULL)
	{
		idx = count_until_pipe(token, idx);
		while (token[idx].type == TYPE_PIPE)
		{
			idx++;
			head = ms_parser_cmdnew(token, &idx, data);
			if (head != NULL)
				break ;
			idx = count_until_pipe(token, idx);
		}
	}
	now = head;
	if (make_cmd_list(token, idx, now, data) == NULL)
		return (ms_clear_cmd_and_return_null(head));
	return (head);
}

void	*ms_clear_cmd_and_return_null(t_cmd *head)
{
	t_cmd	*now;
	t_cmd	*next;

	now = head;
	while (now != NULL)
	{
		next = now->next;
		free(now->path);
		now->path = NULL;
		free(now->arg);
		now->arg = NULL;
		free(now->input);
		now->input = NULL;
		free(now->output);
		now->output = NULL;
		free(now);
		now = NULL;
		now = next;
	}
	return (NULL);
}

static size_t	count_until_pipe(t_token *token, size_t idx)
{
	while (token[idx].str != NULL && token[idx].type != TYPE_PIPE)
		idx++;
	return (idx);
}

static t_cmd	*make_cmd_list(t_token *token, size_t idx, \
		t_cmd *now, t_data *data)
{
	while (token[idx++].type == TYPE_PIPE)
	{
		now->next = ms_parser_cmdnew(token, &idx, data);
		if (now->next != NULL)
			now->next->prev = now;
		now = now->next;
		if (now == NULL)
			return (NULL);
	}
	return (now);
}

static bool	ms_parser_chktokenflag(t_token *token)
{
	size_t	idx;

	idx = 0;
	if (token[idx].type == TYPE_PIPE)
		return (false);
	while (token[idx].str != NULL)
	{
		if (token[idx].type == 0)
			return (false);
		idx++;
	}
	if (idx > 0 && token[idx - 1].type == TYPE_PIPE)
		return (false);
	return (true);
}
