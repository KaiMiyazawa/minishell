/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:08:46 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/15 18:49:32 by miyazawa.ka      ###   ########.fr       */
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

extern int	g_state;

void	data_init(int ac, char **av, char **ev, t_data *data)
{
	data->ac = ac;
	data->av = av;
	data->envp = ev;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data_init(argc, argv, envp, &data);
	minishell();
	return (0);
}

//__attribute__((destructor))
//static void destructor() {
//	system("leaks -q a.out");
//}