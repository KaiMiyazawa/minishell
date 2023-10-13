/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:08:46 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/13 15:04:44 by kmiyazaw         ###   ########.fr       */
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

int main()
{
	char *line = NULL;

	while (1)
	{
		line = readline("> ");
		if (!strcmp(line, "exit"))
		{
			free(line);
			break;
		}
		if (line != NULL && strlen(line) != 0)
			printf("line is '%s'\n", line);
		add_history(line);

		fork
		execve()
		free(line);
	}
	printf("exit\n");
	return 0;
}

__attribute__((destructor))
static void destructor() {
	system("leaks -q a.out");
}