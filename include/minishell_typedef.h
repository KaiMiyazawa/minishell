/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedef.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:02:10 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/28 14:15:24 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPEDEF_H
# define MINISHELL_TYPEDEF_H

//# define FLAG_STRING
//# define FLAG_IN
//# define FLAG_HEREDOC
//# define FLAG_OUT
//# define FLAG_APPEND
//# define FLAG_PIPE
//# define FLAG_RINT

typedef struct sigaction	t_sa;

typedef enum e_tk_type {
	//0 NONE
	NONE,
	//1 文字列
	STR,
	//2 >
	RDIR,
	//3 >>
	RRDIR,
	//4 <
	LDIR,
	//5 <<
	LLDIR,
	/*6   */
	SPACE_,
	//7 '
	SQUOTE,
	//8 single quoteの中身
	SQ_STR,
	//9 "
	DQUOTE,
	//10 double quoteの中身
	DQ_STR,
	//11 |
	PIPE,
	//12 $
	DOLL,
	//13 2>file の[2]
	RINT,
	//14 終端
	NULL_
}				t_tk_type;

typedef struct s_token_list	t_tk_list;

typedef struct s_token_list {
	char			*word;
	t_tk_type		type;
	t_tk_list		*next;
}				t_tk_list;

typedef struct s_token {
	char			*word;
	t_tk_type		type;
}				t_tk;

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
}				t_cmd;

typedef struct s_data
{
	t_list	*environ;//
	char		**envp;
	char		**path;
	pid_t		pid;
	int			line_size;
	char		*line;
	t_tk_list	*tk_head;
	t_tk_list	*tk_tail;
	int			tk_size;
	t_tk		*tk;//
	int			status;
	t_cmd		*cmd;//
	bool		kill_child;//
	bool		heredoc_sigint;//
}				t_data;

#endif
