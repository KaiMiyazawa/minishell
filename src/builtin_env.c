/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:10:36 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:04:39 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_env(char *argv[], t_data *data)
{
	t_list	*now;

	(void)data;
	if (argv == NULL)
		return (0);
	now = data->environ;
	while (now != NULL)
	{
		ft_putendl_fd(now->content, STDOUT_FILENO);
		now = now->next;
	}
	return (0);
}
