/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:52:07 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/11/25 16:14:11 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

//minishell.hは、すべてのinclude、define、関数の宣言を含んでいます。
//ヘッダーファイルは、基本的に一つにまとめるつもりで現状書いています。(宮澤2023/10/29

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
# define SPACE_AND_TAB " \t"

# define DEBUG true
#define TYPE_STR(var) #var

typedef enum e_tk_type {
	STR,		// 文字列
	RDIR,		// >
	RRDIR,		// >>
	LDIR,		// <
	LLDIR,		// <<
	SPACE_,		/*   *///
	SQUOTE,		// '
	DQUOTE,		// "
	PIPE,		// |
	DOLL,		// $
	RINT,		// 2>file の[2]
	NULL_
	//RINTだけ、一文字見ただけでstrかstr以外かの判別でstr以外と認識できない。
	//→これだけ別で処理したい。

	//SSTR,		// single_quote 内の文字列。
	//LLLDIR,	// <<<
	//DPIPE,	// ||
	//AND,		// &
	//DAND,		// &&
	//SCOLON,	// ;
	//DSCOLON,	// ;;
	//ESC,		/* \ */
}				t_tk_type;

typedef struct s_token	t_tk;

typedef struct s_token {
	char			*word;
	t_tk_type	type;
	t_tk	*next;
}				t_tk;

typedef struct s_data
{
	int			ac;
	char		**av;
	char		**envp;

	char			**path;

	int				line_size;
	char			*line;

	int 			in_fd;
	int 			out_fd;

	t_tk			*tk_head;
	t_tk			*tk_tail;
}				t_data;

int	g_state;

//関数の定義は、ファイルのabc順に並べています。
//関数名に_eをつけた関数を作り、エラーハンドリングを内包させる方針でとりあえず書いていってます。



//error.c
void	print_error(char *error_msg, char*addition, int exit_state);

//executer.c
void	executor(t_data *data);

//expander.c
void	expander(t_data *data);

//free.c
void	free_all_data(t_data *data);
void	tk_free_list(t_data *data);

//lexer.c
void	lexer(char *line, t_data *data);

//main.c

//make_path.c
char	**make_path(const char *path_line);

//minishell.c
void	handler(int sig);
void	minishell(t_data *data);

//perser.c
void	perser(t_data *data);

//signals.c
void	handle_signals(void);

//tk_list.c
t_tk_type	tk_get_tktype(char letter);
t_tk	*tk_list_new(char *word, t_tk_type type);
void	tk_list_add_back(t_data *data, t_tk *new);
char	*tk_make_word(char *line, t_tk_type type);


//tk_utils.c
t_tk_type	tk_get_tktype(char letter);

//utils_libft.c
int		ft_strlen(const char *str);
void	*ft_calloc(size_t n, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

//utils_libft2.c
char	*ft_strtrim(char const *s1, char const *set);




//debug.c
void	confirm_data(t_data *data);
void	here_debug(void);
void	confirm_tklist(t_data *data);
void	put_pid(void);



#endif
