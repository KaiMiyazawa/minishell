/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:08:46 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/13 19:03:29 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

//   FUNCTIONS

// readline
// rl_clear_history
// rl_on_new_line
// rl_replace_line
// rl_redisplay
// add_history
// printf
// malloc
// free
// write
// access
// open
// read
// close
// fork
// wait
// waitpid
// wait3
// wait4
// signal
// sigaction
// sigemptyset
// sigaddset
// kill
// exit
// getcwd
// chdir
// stat
// lstat
// fstat
// unlink
// execve
// dup
// dup2
// pipe
// opendir
// readdir
// closedir
// strerror
// perror
// isatty
// ttyname
// ttyslot
// ioctl
// getenv
// tcsetattr
// tcgetattr
// tgetent
// tgetflag
// tgetnum
// tgetstr
// tgoto
// tputs

void	handler(int sig)
{
	if (sig == SIGINT)
		rl_redisplay();
		rl_on_new_line();
}

int main()
{
	char *line = NULL;
	pid_t				pid;
	struct sigaction	sa;
	//int		pid1;


	pid = getpid();
	//printf("%d\n", pid);//プロセス番号の確認
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
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
	return 0;
}

//__attribute__((destructor))
//static void destructor() {
//	system("leaks -q a.out");
//}