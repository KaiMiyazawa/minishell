/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:10:36 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/27 21:52:03 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_builtin_env(char *argv[], t_data *data)
{
	t_list	*cur;

	if (argv == NULL)
		return (0);
	cur = data->environ;
	while (cur != NULL)
	{
		ft_putendl_fd(cur->content, STDOUT_FILENO);
		cur = cur->next;
	}
	return (0);
}
