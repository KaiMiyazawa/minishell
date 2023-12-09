/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:10:50 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/27 22:01:14 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ms_strisdigit(char *str)
{
	if (str == NULL || *str == '\0')
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

int	ms_builtin_exit(char *argv[], t_data *data)
{
	int	status;

	ft_putendl_fd(MSG_EXIT, STDOUT_FILENO);
	if (argv == NULL || argv[0] == NULL || argv[1] == NULL)
		status = data->status;
	else if (argv[2] == NULL)
	{
		if (ms_strisdigit(argv[1]))
			status = ft_atoi(argv[1]);
		else
		{
			ft_putendl_fd(MSG_ARG_NOTNUM, STDERR_FILENO);
			status = 0xff;
		}
	}
	else
	{
		ft_putendl_fd(MSG_ARG_MANY, STDERR_FILENO);
		return (1);
	}
	exit(status);
}
