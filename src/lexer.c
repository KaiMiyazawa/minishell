/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:17:01 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:22:02 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ms_lexer_tokensize(char *line);

t_token	*lexer(t_data *data)
{
	t_token	*token;
	size_t	size;

	size = ms_lexer_tokensize(data->line);
	token = (t_token *)malloc((size + 1) * sizeof(t_token));
	if (token == NULL)
		exit(ENOMEM);
	ms_lexer_gettoken(token, data->line, data);
	return (token);
}

static size_t	ms_lexer_tokensize(char *line)
{
	size_t	size;
	size_t	pos;
	size_t	len;

	if (line == NULL)
		return (0);
	size = 0;
	pos = 0;
	while (*(line + pos) != '\0')
	{
		while (*(line + pos) == CHRS_DELIM[0] || *(line + pos) == CHRS_DELIM[1])
			pos++;
		len = ms_lexer_tokenlen(line + pos);
		if (len > 0)
			size++;
		pos += len;
	}
	return (size);
}
