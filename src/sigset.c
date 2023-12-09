/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:24:09 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/08 17:08:07 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigset_rl(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sighandler_rl;
	sigaction(SIGINT, &sa, NULL);
}

void	sigset_noquit(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	sigset_rl_heredoc(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sighandler_rl_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

void	sigset_exec(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sighandler_exec;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
