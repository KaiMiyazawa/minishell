/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:23:49 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:43:45 by miyazawa.ka      ###   ########.fr       */
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
		g_shell.status = 1;
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
	{
		g_shell.status = 1;
		g_shell.heredoc_sigint = true;
	}
}

void	sighandler_exec(int signum, siginfo_t *info, void *context)
{
	t_cmd	*now;

	(void)context;
	(void)info;
	if (signum == SIGQUIT || signum == SIGINT)
	{
		g_shell.status = 128 + signum;
		g_shell.kill_child = true;
		now = g_shell.cmd;
		while (now != NULL)
		{
			kill(now->pid, signum);
			now = now->next;
		}
		if (signum == SIGQUIT)
			ft_putendl_fd(MSG_SIG_QUIT, STDOUT_FILENO);
		if (signum == SIGINT)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
