/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:03:15 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/27 19:15:16 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	ms_parser_cmdnew_arg_size(t_tk *token, size_t idx);

char	**ms_parser_cmdnew_arg(t_tk *token, size_t i_token, t_data *data)
{
	char	**arg;
	size_t	size;
	size_t	i_arg;

	size = ms_parser_cmdnew_arg_size(token, i_token);
	arg = (char **)ft_calloc_e((size + 1), sizeof(char *), data);
	if (arg == NULL)
		return (NULL);
	i_arg = 0;
	while (token[i_token].word != NULL && token[i_token].type != PIPE)
	{
		if (token[i_token].type == STR)
			arg[i_arg++] = token[i_token].word;
		else
			i_token++;
		if (token[i_token].word != NULL && token[i_token].type != PIPE)
			i_token++;
	}
	arg[size] = NULL;
	return (arg);
}

static size_t	ms_parser_cmdnew_arg_size(t_tk *token, size_t idx)
{
	size_t	size;

	size = 0;
	while (token[idx].word != NULL && token[idx].type != PIPE)
	{
		if (token[idx].type == STR)
			size++;
		else
			idx++;
		if (token[idx].word != NULL && token[idx].type != PIPE)
			idx++;
	}
	return (size);
}