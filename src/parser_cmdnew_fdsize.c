/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmdnew_fdsize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:21:12 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/08 17:20:24 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_parser_cmdnew_fdsize(t_token *token, size_t idx, int type)
{
	ssize_t	size;

	size = 0;
	while (token[idx].str != NULL && token[idx].type != TYPE_PIPE)
	{
		if ((token[idx++].type & type) == type)
		{
			if (token[idx++].type != TYPE_STRING)
				return (-1);
			size++;
		}
	}
	return (size);
}
