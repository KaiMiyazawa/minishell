/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmdnew_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:19:53 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:37:16 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ms_parser_cmdnew_arg_size(t_token *token, size_t idx);

char	**ms_parser_cmdnew_arg(t_token *token, size_t i_token)
{
	char	**arg;
	size_t	size;
	size_t	arg_count;

	size = ms_parser_cmdnew_arg_size(token, i_token);
	arg = (char **)malloc((size + 1) * sizeof(char *));
	if (arg == NULL)
		return (NULL);
	arg_count = 0;
	while (token[i_token].str != NULL && token[i_token].type != TYPE_PIPE)
	{
		if (token[i_token].type == TYPE_STRING)
			arg[arg_count++] = token[i_token].str;
		else
			i_token++;
		if (token[i_token].str != NULL && token[i_token].type != TYPE_PIPE)
			i_token++;
	}
	arg[size] = NULL;
	return (arg);
}

static size_t	ms_parser_cmdnew_arg_size(t_token *token, size_t idx)
{
	size_t	size;

	size = 0;
	while (token[idx].str != NULL && token[idx].type != TYPE_PIPE)
	{
		if (token[idx].type == TYPE_STRING)
			size++;
		else
			idx++;
		if (token[idx].str != NULL && token[idx].type != TYPE_PIPE)
			idx++;
	}
	return (size);
}
