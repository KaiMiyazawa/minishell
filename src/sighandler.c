/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:23:49 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/11 17:17:13 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler_rl(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT)
		ms_builtin_exit(NULL, NULL);
	if (signum == SIGINT)
	{
		g_signum = signum;
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sighandler_rl_heredoc(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
		g_signum = signum;
}

void	sighandler_exec(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT || signum == SIGINT)
	{
		g_signum = signum;
		if (signum == SIGQUIT)
			ft_putendl_fd(MSG_SIG_QUIT, STDOUT_FILENO);
		if (signum == SIGINT)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
