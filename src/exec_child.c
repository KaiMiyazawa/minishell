/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:12:55 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/17 12:44:15 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exec_a_cmd(t_data *data, \
	int prev_pipe[2], int now_pipe[2], char **envp);
static void	ms_exec_a_cmd_sub(t_cmd *cmd, char **envp, t_data *data);
static void	ms_wait_all(t_cmd *cmd_lst, t_data *data);
static void	ms_handle_status(int status, t_data *data);

void	ms_exec_in_child_process(t_cmd *cmd, t_data *data)
{
	int		prev_pipe[2];
	int		now_pipe[2];
	t_cmd	*now_cmd;
	char	**envp;

	envp = ms_map_lst2map(data->environ);
	if (envp == NULL)
		return ;
	ms_init_fd(prev_pipe);
	now_cmd = cmd;
	while (now_cmd != NULL)
	{
		if (now_cmd->next != NULL)
			pipe(now_pipe);
		else
			ms_init_fd(now_pipe);
		data->now_cmd = now_cmd;
		ms_exec_a_cmd(data, prev_pipe, now_pipe, envp);
		ms_fd_close(prev_pipe);
		ms_fd_copy(prev_pipe, now_pipe);
		now_cmd = now_cmd->next;
	}
	free(envp);
	envp = NULL;
	return (ms_wait_all(cmd, data));
}

static void	\
	ms_exec_a_cmd(t_data *data, int prev_pipe[2], int now_pipe[2], char **envp)
{
	int		fd[2];
	t_cmd	*cmd;

	cmd = data->now_cmd;
	data->now_cmd = NULL;
	fd[0] = prev_pipe[0];
	fd[1] = now_pipe[1];
	if (ms_fd_last_fd(cmd->input) > 0)
		fd[0] = ms_fd_last_fd(cmd->input);
	if (ms_fd_last_fd(cmd->output) > 0)
		fd[1] = ms_fd_last_fd(cmd->output);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		ms_fd_close(fd);
		ms_fd_close(prev_pipe);
		ms_fd_close(now_pipe);
		ms_exec_a_cmd_sub(cmd, envp, data);
	}
}

static void	ms_exec_a_cmd_sub(t_cmd *cmd, char **envp, t_data *data)
{
	int		(*builtin)(char *arg[], t_data *data);

	if (cmd->path[0] == '\0')
	{
		ft_putendl_fd(MSG_NO_CMD, STDERR_FILENO);
		exit(127);
	}
	if (ms_is_directory(cmd->path))
	{
		ft_putendl_fd(MSG_ISDIR, STDERR_FILENO);
		exit(126);
	}
	builtin = ms_builtin_getfunc(cmd->arg[0]);
	if (builtin != NULL)
		exit(builtin(cmd->arg, data));
	else
	{
		errno = 0;
		execve(cmd->path, cmd->arg, envp);
		if (errno != 0)
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
}

static void	ms_wait_all(t_cmd *cmd_lst, t_data *data)
{
	int		status;
	t_cmd	*now_cmd;
	t_cmd	*tmp;

	now_cmd = cmd_lst;
	while (now_cmd != NULL)
	{
		waitpid(now_cmd->pid, &status, 0);
		if (g_signum == SIGINT || g_signum == SIGQUIT)
		{
			tmp = now_cmd->next;
			while (tmp != NULL && kill(tmp->pid, g_signum))
				tmp = tmp->next;
		}
		ms_handle_status(status, data);
		now_cmd = now_cmd->next;
	}
	ms_fd_close_all_cmd(cmd_lst);
	return ;
}

static void	ms_handle_status(int status, t_data *data)
{
	if (g_signum == SIGINT || g_signum == SIGQUIT)
	{
		data->status = 128 + g_signum;
		g_signum = -1;
		return ;
	}
	if (WIFEXITED(status) && g_signum == -1)
		data->status = WEXITSTATUS(status);
	else
		return ;
}
