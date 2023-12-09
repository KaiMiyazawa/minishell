/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:09:11 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/02 20:03:14 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_echo(char *argv[], t_data *data)
{
	bool		print_nl;
	size_t		start;
	size_t		i;

	(void)data;
	if (argv[0] == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (1);
	}
	print_nl = !(argv[1] && ft_strcmp(argv[1], OPTION_NONL) == 0);
	start = 2 - print_nl;
	i = start;
	while (argv[i] != NULL)
	{
		if (i > start)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	}
	if (print_nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
