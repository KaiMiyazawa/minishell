/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:13:48 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:14:19 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cmdsize(t_cmd *cmd);

void	executer(t_cmd *cmd, t_data *data)
{
	int	(*builtin)(char *arg[], t_data *data);

	if (cmd == NULL)
		return ;
	builtin = ms_builtin_getfunc(cmd->arg[0]);
	if (builtin != NULL && ms_cmdsize(cmd) == 1)
		ms_exec_a_builtin(cmd, builtin, data);
	else
		ms_exec_in_child_process(cmd, data);
	ms_clear_cmd_and_return_null(cmd);
}

static int	ms_cmdsize(t_cmd *cmd)
{
	int	size;

	size = 0;
	while (cmd != NULL)
	{
		size++;
		cmd = cmd->next;
	}
	return (size);
}
