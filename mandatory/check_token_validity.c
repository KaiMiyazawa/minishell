/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_validity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:51:54 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/24 18:40:27 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

bool	simple_invalid_case(t_data *data)
{
	if (data->tk_head->type == PIPE
		|| data->tk_tail->type == PIPE)
	{
		put_unexpected_token_error("|");
		tk_free_list(data);
		return (true);
	}
	if (data->tk_tail->type == LDIR
		|| data->tk_tail->type == RDIR
		|| data->tk_tail->type == LLDIR
		|| data->tk_tail->type == RRDIR)
	{
		put_unexpected_token_error("newline");
		tk_free_list(data);
		return (true);
	}
	return (false);
}

bool	complex_invalid_case(t_data *data)
{

}

bool	check_token_validity(t_data *data)
{
	if (simple_invalid_case(data) == true)
		return (true);
	if (consecutive_invalid_case(data) == true)
		return (true);
	if (conplex_invalid_case(data) == true)
		return (true);
	return (true);
}

