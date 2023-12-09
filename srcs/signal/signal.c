/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:33:49 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/28 14:18:08 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_builtin_exit_for_sig(char *argv[])
{
	int	status;

	ft_putendl_fd(MSG_EXIT, STDOUT_FILENO);
	if (argv == NULL || argv[0] == NULL || argv[1] == NULL)
		status = 1;
	else if (argv[2] == NULL)
	{
		if (ms_strisdigit(argv[1]))
			status = ft_atoi(argv[1]);
		else
		{
			ft_putendl_fd(MSG_ARG_NOTNUM, STDERR_FILENO);
			status = 0xff;
		}
	}
	else
	{
		ft_putendl_fd(MSG_ARG_MANY, STDERR_FILENO);
		return (1);
	}
	exit(status);
}

void	ms_sighandler_rl(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT)
		ms_builtin_exit_for_sig(NULL);
	if (signum == SIGINT)
	{
		g_sig_num = signum;
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}


void	ms_sighandler_rl_heredoc(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
		g_sig_num = signum;

}

void	ms_sighandler_exec(int signum, siginfo_t *info, void *context)
{
	t_cmd	*cur;

	(void)context;
	(void)info;
	if (signum == SIGQUIT || signum == SIGINT)
	{
		g_sig_num = signum;
		cur = g_cmd_ptr;
		while (cur != NULL)
		{
			kill(cur->pid, signum);
			cur = cur->next;
		}
		if (signum == SIGQUIT)
			ft_putendl_fd(MSG_SIG_QUIT, STDOUT_FILENO);
		if (signum == SIGINT)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
}




//===============================

void	ms_sigset_rl(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ms_sighandler_rl;
	sigaction(SIGINT, &sa, NULL);
}

void	ms_sigset_noquit(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ms_sigset_rl_heredoc(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ms_sighandler_rl_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

void	ms_sigset_exec(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ms_sighandler_exec;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
