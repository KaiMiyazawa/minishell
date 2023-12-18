/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:12:43 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/10 14:52:42 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_a_builtin(t_cmd *cmd, int (*builtin)(char *arg[],
		t_data *data), t_data *data)
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

int	(*ms_builtin_getfunc(char *arg))(char *argv[], t_data *data)
{
	if (ft_strcmp(arg, "echo") == 0)
		return (ms_builtin_echo);
	else if (ft_strcmp(arg, "cd") == 0)
		return (ms_builtin_cd);
	else if (ft_strcmp(arg, "pwd") == 0)
		return (ms_builtin_pwd);
	else if (ft_strcmp(arg, "export") == 0)
		return (ms_builtin_export);
	else if (ft_strcmp(arg, "unset") == 0)
		return (ms_builtin_unset);
	else if (ft_strcmp(arg, "env") == 0)
		return (ms_builtin_env);
	else if (ft_strcmp(arg, "exit") == 0)
		return (ms_builtin_exit);
	return (0);
}
