/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:37:12 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/29 21:57:25 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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

void	ms_exec_a_builtin(t_cmd *cmd, int (*builtin)(char *arg[], t_data *data), t_data *data)
{
	int	tmp_fd[2];
	int	use_fd[2];

	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	use_fd[0] = ms_fd_last_fd(cmd->input);
	use_fd[1] = ms_fd_last_fd(cmd->output);
	if (use_fd[0] > STDIN_FILENO)
		dup2(use_fd[0], STDIN_FILENO);
	if (use_fd[1] >= STDIN_FILENO && use_fd[1] != STDOUT_FILENO)
		dup2(use_fd[1], STDOUT_FILENO);
	data->status = builtin(cmd->arg, data);
	ms_fd_close_all_cmd(cmd);
	dup2(tmp_fd[0], STDIN_FILENO);
	dup2(tmp_fd[1], STDOUT_FILENO);
	ms_fd_close(tmp_fd);
}

void	executer(t_data *data)
{
		int	(*builtin)(char *arg[], t_data *data);

	if (data->cmd == NULL)
		return ;
	builtin = ms_builtin_getfunc(data->cmd->arg[0]);
	if (builtin != NULL && ms_cmdsize(data->cmd) == 1)
		ms_exec_a_builtin(data->cmd, builtin, data);
	else
		ms_exec_in_child_process(data->cmd, data);
	ms_clear_cmd_and_return_null(data->cmd);
}
