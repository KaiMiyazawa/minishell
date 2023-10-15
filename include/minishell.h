/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:52:07 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/15 15:50:19 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
#include <dirent.h>

typedef struct s_data
{
	int			ac;
	char		**av;
	char		**envp;


}				t_data;

void	handler(int sig);
void	minishell(void);



#endif