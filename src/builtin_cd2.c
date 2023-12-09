/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:23:38 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:42:17 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
