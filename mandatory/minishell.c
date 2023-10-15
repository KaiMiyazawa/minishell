/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:31:59 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/15 14:00:27 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
		rl_on_new_line();
		//rl_redisplay();
}

void	handle_signals()
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit (1);
}

void	minishell(void)
{
	char				*line;

	//killコマンドで挙動確認する用
	pid_t				pid;
	pid = getpid();
	printf("%d\n", pid);//プロセス番号の確認

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (!strcmp(line, "exit"))
		{
			free(line);
			break;
		}
		if (strlen(line) != 0)
			printf("line is '%s'\n", line);
		add_history(line);
		free(line);
		line = NULL;
	}
	printf("exit\n");
}
