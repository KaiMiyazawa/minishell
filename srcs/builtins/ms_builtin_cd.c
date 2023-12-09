/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:09:55 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/27 22:17:58 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ms_builtin_cd(char *argv[], t_data *data);
static int	ms_builtin_cd_env(char	*key, t_data *data);
static int	ms_builtin_cd_chdir(char *path, t_data *data);
static int	ms_builtin_cd_export(char *key, char *val, t_data *data);


void	ms_setpath_home(char *path, char *arg, t_data *data)
{
	ft_strlcpy(path, ms_getenv_val(ENV_HOME, data), PATH_MAX + 1);
	ft_strlcat(path, &arg[1], PATH_MAX + 1);
}

void	ms_setpath_absolute(char *path, char *arg)
{
	ft_strlcpy(path, arg, PATH_MAX + 1);
}

void	ms_setpath_relative(char *path, char *arg, t_data *data)
{
	char	*pwd;
	char	cwd[PATH_MAX + 1];

	pwd = ms_getenv_val("PWD", data);
	if (pwd == NULL)
		ft_strlcpy(path, getcwd(cwd, PATH_MAX), PATH_MAX + 1);
	else
		ft_strlcpy(path, pwd, PATH_MAX + 1);
	if (path[1] != '\0' && path[1] != '/')
		ft_strlcat(path, STR_DIR, PATH_MAX + 1);
	ft_strlcat(path, arg, PATH_MAX + 1);
}

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
	char	*val;

	val = ms_getenv_val(key, data);
	if (val)
		return (ms_builtin_cd_chdir(val, data));
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
	char	*keyval;
	size_t	len;

	if (key == NULL || val == NULL)
		return (1);
	len = ft_strlen(key) + 1;
	keyval = (char *)malloc((len + ft_strlen(val) + 1) * sizeof(char));
	if (keyval == NULL)
		return (errno);
	ft_strlcpy(keyval, key, len);
	ft_strlcpy(keyval + len, val, ft_strlen(val) + 1);
	ms_search_env_and_set(keyval, data);
	free(keyval);
	return (0);
}
