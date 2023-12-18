/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:09:55 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/17 15:50:17 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_builtin_cd_env(char	*key, t_data *data);
static int	ms_builtin_cd_chdir(char *path, t_data *data);
static int	ms_builtin_cd_export(char *key, char *val, t_data *data);

int	ms_builtin_cd(char	*argv[], t_data *data)
{
	char	path[PATH_MAX + 1];
	int		status;

	if (argv == NULL || argv[1] == NULL)
		return (ms_builtin_cd_env(ENV_HOME, data));
	else if (argv[1][0] == '~' \
		&& (argv[1][1] == '/' || argv[1][1] == '\0'))
	{
		if (ms_getenv_val(ENV_HOME, data) == NULL)
			return (ms_builtin_cd_env(ENV_HOME, data));
		ms_setpath_home(path, argv[1], data);
	}
	else if (ft_strcmp(argv[1], STR_OLDPWD) == 0)
		return (ms_builtin_cd_env(ENV_OLDPWD, data));
	else if (argv[1][0] == '/')
		ms_setpath_absolute(path, argv[1]);
	else
		ms_setpath_relative(path, argv[1], data);
	status = ms_builtin_cd_chdir(path, data);
	return (status);
}

static int	ms_builtin_cd_env(char	*key, t_data *data)
{
	char	*value;

	value = ms_getenv_val(key, data);
	if (value)
		return (ms_builtin_cd_chdir(value, data));
	else if (ft_strcmp(key, ENV_HOME) == 0)
		ft_putendl_fd(MSG_NO_HOME, STDERR_FILENO);
	else if (ft_strcmp(key, ENV_OLDPWD) == 0)
		ft_putendl_fd(MSG_NO_OLDPWD, STDERR_FILENO);
	else
		return (ms_builtin_cd_chdir(NULL, data));
	return (1);
}

static int	ms_builtin_cd_chdir(char *path, t_data *data)
{
	if (path == NULL || chdir(path))
	{
		ft_putendl_fd(MSG_ENOENT, STDERR_FILENO);
		return (1);
	}
	ms_builtin_cd_export(ENV_OLDPWD, ms_getenv_val("PWD", data), data);
	if (path[0] == '/' && path[1] == '/' && path[2] != '/')
		getcwd(path + 1, PATH_MAX - 1);
	else
		getcwd(path, PATH_MAX);
	ms_builtin_cd_export("PWD", path, data);
	return (0);
}

static int	ms_builtin_cd_export(char *key, char *val, t_data *data)
{
	char	*key_value;
	size_t	len;

	if (key == NULL || val == NULL)
		return (1);
	len = ft_strlen(key) + 1;
	key_value = (char *)ft_calloc((len + ft_strlen(val) + 1), sizeof(char));
	if (key_value == NULL)
		return (errno);
	ft_strlcpy(key_value, key, len);
	ft_strlcpy(key_value + len, val, ft_strlen(val) + 1);
	ms_search_env_and_set(key_value, data, data->environ);
	free(key_value);
	key_value = NULL;
	return (0);
}
