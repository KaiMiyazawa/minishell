/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:25:16 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/25 17:12:20 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_all_data(t_data *data)
{
	int	count;

	count = -1;
	while (data->path[++count])
	{
		free(data->path[count]);
	}
	free(data->path[count]);
	free(data->path);
	if (data->tk_head)
		tk_free_list(data);
	if (data->line)
		free(data->line);
	data->line = NULL;
	data->line_size = 0;
	return ;
}

void	tk_free_list(t_data *data)
{
	t_tk	*tmp;
	t_tk	*tmp2;

	tmp = data->tk_head;
	while (tmp->next != NULL)
	{
		tmp2 = tmp->next;
		free(tmp->word);
		free(tmp);
		tmp = tmp2;
	}
	free(tmp->word);
	free(tmp);
	data->tk_head = NULL;
	data->tk_tail = NULL;
	return ;
}
