/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:11:17 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/02 20:02:59 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_pwd(char *argv[], t_data *data)
{
	char	cwd[PATH_MAX + 1];
	char	*pwd;

	if (argv == NULL)
		return (0);
	errno = 0;
	getcwd(cwd, PATH_MAX);
	pwd = ms_getenv_val("PWD", data);
	if (pwd != NULL && ft_strcmp(cwd, pwd + 1) == 0)
		ft_strlcpy(cwd, pwd, PATH_MAX + 1);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (errno);
}
