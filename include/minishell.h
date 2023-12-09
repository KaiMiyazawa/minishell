/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:42:41 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/29 22:00:39 by miyazawa.ka      ###   ########.fr       */
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
# include <limits.h>

# include "../libft/libft.h"
# include "minishell_typedef.h"
# include "minishell_constants.h"

int		g_sig_num;

t_cmd	*g_cmd_ptr;

char		**make_path(const char *path_line);
void		minishell(t_data *data);

void		here_debug(void);

void		confirm_data(t_data *data);
void		confirm_tklist(t_data *data);


t_tk_list	*tk_list_new(char *word, t_tk_type type);
bool		tk_list_add_back(t_data *data, t_tk_list *new);
char		*tk_make_word(char *line, t_tk_type type);


void		expander(t_data *data);

t_tk_type	tk_get_tktype(char letter);
void		lexer(t_data *data, char *line);
void		executer(t_data *data);
bool		parser(t_data *data);

void		free_all_data(t_data *data, bool exit_flag);
void		tk_free_list(t_data *data);
void		put_error_destroy_data_exit(
				t_data *data, char *error_msg, int status);
bool		put_error_destroy_data_continue(t_data *data,
				char *error_msg, int state);

void		confirm_tk(t_data *data);
void		*ft_calloc_e(size_t n, size_t size, t_data *data);
void	*ms_clear_cmd_and_return_null(t_cmd *head);
char	**ms_parser_cmdnew_arg(t_tk *token, size_t i_token, t_data *data);
char	*ms_getpath_cmd(char *name, t_data* data);
char	*ft_strdup_e(char *s, t_data *data);
t_list	*ft_lstnew_e(void *content, t_data *data);


int		ms_builtin_cd(char *argv[], t_data *data);
int		ms_builtin_echo(char *argv[], t_data *data);
int		ms_builtin_env(char *argv[], t_data *data);
int		ms_builtin_exit(char *argv[], t_data *data);
int		ms_builtin_export(char *argv[], t_data *data);
void	ms_search_env_and_set(char *env_key, t_data *data);
int		ms_builtin_pwd(char *argv[], t_data *data);
int		ms_builtin_unset(char *argv[], t_data *data);
int		ms_builtin_cd(char	*argv[], t_data *data);

char	*ms_getenv_val(char *env_key, t_data *data);
bool	ms_is_validenv(char *env_candidate);
bool	ms_is_same_envkey(char *dest, char *src);


void	ms_sigset_rl(void);
void	ms_sigset_noquit(void);
void	ms_sigset_rl_heredoc(void);
void	ms_sigset_exec(void);
bool	ms_strisdigit(char *str);

int	(*ms_builtin_getfunc(char *arg))(char *argv[], t_data *data);

void		ms_fd_close(int fd[2]);
void		ms_fd_copy(int dest[2], int src[2]);
int			ms_fd_last_fd(t_fd *fd_lst);
void		ms_fd_close_all_cmd(t_cmd *cmd);
//static void	ms_fd_close_fds(t_fd *fd);


void		ms_exec_in_child_process(t_cmd *cmd, t_data *data);

char	**ms_map_lst2map(t_list *lst);


#endif
