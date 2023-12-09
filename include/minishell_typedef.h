/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedef.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:29:02 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/08 17:16:36 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPEDEF_H
# define MINISHELL_TYPEDEF_H

# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct sigaction	t_sa;

typedef struct s_token {
	char	*str;
	int		type;
}	t_token;

typedef struct s_fd {
	char	*path;
	int		fd;
}	t_fd;

typedef struct s_cmd {
	char			*path;
	char			**arg;
	t_fd			*input;
	t_fd			*output;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	pid_t			pid;
}	t_cmd;

typedef struct s_shell {
	int		status;
	t_cmd	*cmd;
	bool	kill_child;
	bool	heredoc_sigint;
}	t_shell;

typedef struct s_data {
	char	*line;
	t_token	*token;
	t_list	*environ;
	t_cmd	*now_cmd;
}	t_data;

#endif
