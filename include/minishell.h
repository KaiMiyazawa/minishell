/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:52:07 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/21 09:57:19 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <stdbool.h>

# define FAILED -1

typedef struct s_data
{
	int			ac;
	char		**av;
	char		**envp;

}				t_data;

//関数名に_eをつけた関数を作り、エラーハンドリングを内包させる
//というのが僕のだいたいの習慣です。

void	handler(int sig);
void	minishell(t_data *data);

//utils_libft.c
int		ft_strlen(const char *str);
void	*ft_calloc(size_t n, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

//
void	lexer(char *line, t_data *data);
void	perser(t_data *data);
void	evaluater(t_data *data);

#endif
