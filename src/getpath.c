/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:14:45 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/17 15:50:53 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_getpath_relative(char *name, t_data *data);
static char	*ms_getpath_envpath(char *name, t_data *data);
static char	*ms_getpath_envpath_iter(char *name, \
				char **envpath_split);
static char	*ms_getpath_join(char *dirpath, char *name);

char	*ms_getpath_cmd(char *name, t_data *data)
{
	if (name == NULL)
		return (NULL);
	if (ms_builtin_getfunc(name))
		return (ft_strdup(name));
	else if (*name == '/')
		return (ft_strdup(name));
	else if (ft_strchr(name, '/'))
		return (ms_getpath_relative(name, data));
	return (ms_getpath_envpath(name, data));
}

static char	*ms_getpath_relative(char *name, t_data *data)
{
	char	*path;
	char	*pwd;
	char	cwd[PATH_MAX + 1];

	pwd = ms_getenv_val("PWD", data);
	if (pwd == NULL)
		path = ms_getpath_join(getcwd(cwd, PATH_MAX), name);
	else
		path = ms_getpath_join(pwd, name);
	return (path);
}

static char	*ms_getpath_envpath(char *name, t_data *data)
{
	char		*cmdpath;
	char		*envpath;
	char		**envpath_split;

	envpath = ms_getenv_val(ENV_PATH, data);
	if (envpath == NULL)
		return (ft_strdup(name));
	envpath_split = ft_split(envpath, ':');
	if (envpath_split == NULL)
		return (NULL);
	cmdpath = ms_getpath_envpath_iter(name, envpath_split);
	envpath_split = ms_map_clear(envpath_split, ms_map_size(envpath_split));
	if (!cmdpath)
		cmdpath = ft_strdup(STR_EMPTY);
	return (cmdpath);
}

static char	*ms_getpath_envpath_iter(char *name, char **envpath_split)
{
	char		*cmdpath;
	struct stat	stat_buf;
	size_t		i;

	if (envpath_split == NULL)
		return (NULL);
	i = 0;
	while (envpath_split[i])
	{
		ft_memset(&stat_buf, 0, sizeof(struct stat));
		cmdpath = ms_getpath_join(envpath_split[i], name);
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

static char	*ms_getpath_join(char *dirpath, char *name)
{
	char	*path;
	size_t	dir_len;
	size_t	name_len;

	dir_len = ft_strlen(dirpath);
	name_len = ft_strlen(name);
	path = (char *)ft_calloc((dir_len + name_len + 2), sizeof(char));
	if (path == NULL)
		return (NULL);
	ft_strlcpy(path, dirpath, dir_len + 1);
	*(path + dir_len) = '/';
	ft_strlcpy(path + dir_len + 1, name, name_len + 1);
	return (path);
}
