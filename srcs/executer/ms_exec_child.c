/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:12:55 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/29 22:13:36 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ms_exec_in_child_process(t_cmd *cmd, t_data *data);
static void	ms_exec_a_cmd(t_cmd *cmd, \
	int prev_pipe[2], int now_pipe[2], t_data *data);
static void	ms_exec_a_cmd_sub(t_cmd *cmd, char **envp, t_data *data);
static void	ms_wait_all(t_cmd *cmd_lst, t_data *data);
static void	ms_handle_status(int status, t_data *data);

void	ms_init_fd(int fd[2])
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
}

bool	ms_is_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) != 0)
		return (false);
	if (S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}

void	ms_exec_in_child_process(t_cmd *cmd, t_data *data)
{
	int		prev_pipe[2];
	int		now_pipe[2];
	t_cmd	*now_cmd;

	data->envp = ms_map_lst2map(data->environ);
	if (data->envp == NULL)
		return ;
	ms_init_fd(prev_pipe);
	now_cmd = cmd;
	while (now_cmd != NULL)
	{
		if (now_cmd->next != NULL)
			pipe(now_pipe);
		else
			ms_init_fd(now_pipe);
		ms_exec_a_cmd(now_cmd, prev_pipe, now_pipe, data);
		ms_fd_close(prev_pipe);
		ms_fd_copy(prev_pipe, now_pipe);
		now_cmd = now_cmd->next;
	}
	free(data->envp);
	return (ms_wait_all(cmd, data));
}

void	\
	ms_exec_a_cmd(t_cmd *cmd, int prev_pipe[2], int now_pipe[2], t_data *data)
{
	int		fd[2];

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
		ms_exec_a_cmd_sub(cmd, data->envp, data);
	}
}

void	ms_exec_a_cmd_sub(t_cmd *cmd, char **envp, t_data *data)
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

void	ms_wait_all(t_cmd *cmd_lst, t_data *data)
{
	int		status;
	t_cmd	*now_cmd;

	now_cmd = cmd_lst;
	while (now_cmd != NULL)
	{
		waitpid(now_cmd->pid, &status, 0);
		ms_handle_status(status, data);
		now_cmd = now_cmd->next;
	}
	data->kill_child = false;
	ms_fd_close_all_cmd(cmd_lst);
	return ;
}

void	ms_handle_status(int status, t_data *data)
{
	if (WIFEXITED(status) && data->kill_child == false)
		data->status = WEXITSTATUS(status);
	else
		return ;
}



//--------------
char	**ms_map_lst2map(t_list *lst)
{
	char	**map;
	t_list	*ele;
	size_t	size;
	size_t	i;

	size = ft_lstsize(lst);
	ele = lst;
	map = (char **)malloc((size + 1) * sizeof(char *));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		map[i] = ele->content;
		ele = ele->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}