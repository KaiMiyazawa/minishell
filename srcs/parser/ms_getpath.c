/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:14:45 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/27 21:59:51 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ms_getpath_cmd(char *name, t_data *data);
char	*ms_getpath_relative_e(char *name, t_data *data);
char	*ms_getpath_envpath(char *name, t_data *data);
char	*ms_getpath_envpath_iter(char *name, char **envpath_split, t_data *data);
char	*ms_getpath_join(char *dirpath, char *name, t_data *data);

void	*free_and_return(void *malloc_obj)
{
	free(malloc_obj);
	return (NULL);
}





size_t	ms_map_size(char **map)
{
	size_t	i;

	if (map == NULL)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	*ms_map_clear(char **map, size_t size)
{
	size_t	i;

	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		free(map[i++]);
	free(map);
	map = NULL;
	return (NULL);
}






bool	ms_is_same_envkey(char *dest, char *src)
{
	return (ft_strncmp(dest, src, ft_strlen(src)) == 0 \
			&& dest[ft_strlen(src)] == '=');
}

char	*ms_getenv_line(char *env_key, t_data *data)
{
	t_list	*cur;

	cur = data->environ;
	while (cur != NULL)
	{
		if (ms_is_same_envkey(cur->content, env_key))
			return (cur->content);
		cur = cur->next;
	}
	return (NULL);
}

char	*ms_getenv_val(char *env_key, t_data *data)
{
	char	*env_line;

	env_line = ms_getenv_line(env_key, data);
	if (env_line == NULL)
		return (NULL);
	return (ft_strchr(env_line, '=') + 1);
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




//this is the main function of this file
char	*ms_getpath_cmd(char *name, t_data* data)
{
	if (name == NULL)
		return (NULL);
	if (ms_builtin_getfunc(name))
		return (ft_strdup_e(name, data));
	else if (*name == '/')
		return (ft_strdup_e(name, data));
	else if (ft_strchr(name, '/'))
		return (ms_getpath_relative_e(name, data));
	return (ms_getpath_envpath(name, data));
}

char	*ms_getpath_relative_e(char *name, t_data *data)
{
	char	*path;
	char	*pwd;
	char	cwd[PATH_MAX + 1];

	pwd = ms_getenv_val("PWD", data);
	if (pwd == NULL)
		path = ms_getpath_join(getcwd(cwd, PATH_MAX), name, data);
	else
		path = ms_getpath_join(pwd, name, data);
	return (path);
}

char	*ms_getpath_envpath(char *name, t_data *data)
{
	char		*cmdpath;
	char		*envpath;
	char		**envpath_split;

	envpath = ms_getenv_val(ENV_PATH, data);
	if (envpath == NULL)
		return (ft_strdup(name));
	envpath_split = ft_split(envpath, ':');
	if (envpath_split == NULL)
		put_error_destroy_data_exit(data, "malloc error", 12);
	cmdpath = ms_getpath_envpath_iter(name, envpath_split, data);
	envpath_split = ms_map_clear(envpath_split, ms_map_size(envpath_split));
	if (!cmdpath)
		cmdpath = ft_strdup(STR_EMPTY);
	return (cmdpath);
}

char	*ms_getpath_envpath_iter(char *name, char **envpath_split, t_data *data)
{
	char		*cmdpath;
	struct stat	stat_buf;
	size_t		i;

	if (envpath_split == NULL)
		return (NULL);
	i = 0;
	while (envpath_split[i])
	{
		cmdpath = ms_getpath_join(envpath_split[i], name, data);
		if (cmdpath == NULL)
			return (ms_map_clear(envpath_split, ms_map_size(envpath_split)));
		stat(cmdpath, &stat_buf);
		if ((stat_buf.st_mode & S_IFMT) == S_IFREG)
			return (cmdpath);
		cmdpath = free_and_return(cmdpath);
		i++;
	}
	return (NULL);
}

char	*ms_getpath_join(char *dirpath, char *name, t_data *data)
{
	char	*path;
	size_t	len_dir;
	size_t	len_name;

	len_dir = ft_strlen(dirpath);
	len_name = ft_strlen(name);
	path = (char *)ft_calloc_e((len_dir + len_name + 2), sizeof(char), data);
	if (path == NULL)
		return (NULL);
	ft_strlcpy(path, dirpath, len_dir + 1);
	*(path + len_dir) = '/';
	ft_strlcpy(path + len_dir + 1, name, len_name + 1);
	return (path);
}
