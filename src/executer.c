/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:13:48 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/17 16:19:19 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cmdsize(t_cmd *cmd);

void	executer(t_cmd *cmd, t_data *data)
{
	int	(*builtin)(char *arg[], t_data *data);

	sigset_exec();
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
