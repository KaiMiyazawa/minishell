/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_gettoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:15:27 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/17 12:36:50 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_lexer_gettoken_classify(char *line);

void	ms_lexer_gettoken(t_token *token, char *line, t_data *data)
{
	char	*str;
	size_t	count;
	size_t	len;
	size_t	i;

	count = 0;
	i = 0;
	while (*(line + count) != '\0')
	{
		while (*(line + count) == ' ' || *(line + count) == '\t')
			count++;
		len = ms_lexer_tokenlen(line + count);
		str = ft_substr(line, count, len);
		if (str == NULL)
			exit(ENOMEM);
		token[i].type = ms_lexer_gettoken_classify(str);
		token[i].str = ms_lexer_string(str, data);
		free(str);
		str = NULL;
		count += len;
		if (token[i].str != NULL)
			i++;
	}
	token[i].str = NULL;
	return ;
}

static int	ms_lexer_gettoken_classify(char *line)
{
	int		type;

	if (line == NULL)
		return (0x00);
	if (!ft_strchr(CHRS_DELIM, *line))
		return (TYPE_STRING);
	type = 0x00;
	if (*line == '<')
		type = TYPE_IN;
	else if (*line == '>')
		type = TYPE_OUT;
	else if (*line == '|')
		type = TYPE_PIPE;
	if (*(line + 1) == '\0')
		return (type);
	else if (*line == *(line + 1))
		type += type >> SHIFT_TYPE;
	if (*(line + 2) == '\0' && *(line + 1) != '|')
		return (type);
	return (0x00);
}
