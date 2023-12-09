/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:20:02 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/15 18:23:38 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static bool	is_space_3(char letter)
{
	if (11 <= letter && 15 >= letter)
		return (true);
	if (letter == ' ')
		return (true);
	return (false);
}

t_tk_type	tk_get_tktype(char letter)
{
	if (is_space_3(letter))
		return (SPACE_);
	if (letter == 39)
		return (SQUOTE);
	if (letter == 34)
		return (DQUOTE);
	if (letter == '|')
		return (PIPE);
	if (letter == '$')
		return (DOLL);
	if (letter == '>')
		return (RDIR);
	if (letter == '<')
		return (LDIR);
	return (STR);
}