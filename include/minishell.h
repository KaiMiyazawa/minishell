/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:28:24 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/13 16:20:41 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"
# include "minishell_typedef.h"
# include "minishell_constants.h"

extern int		g_signum;

void	sigset_rl(void);
void	sigset_rl_heredoc(void);
void	sigset_exec(void);
void	sigset_noquit(void);
void	sighandler_rl(int signum, siginfo_t *info, void *context);
void	sighandler_rl_heredoc(int signum, siginfo_t *info, void *context);
void	sighandler_exec(int signum, siginfo_t *info, void *context);

t_token	*lexer(t_data *data);

void	ms_lexer_gettoken(t_token *token, char *line, t_data *data);

size_t	ms_lexer_tokenlen(char *line);
size_t	ms_lexer_tokenlen_quoted(char *line);
size_t	ms_lexer_tokenlen_plain(char *line);

char	*ms_lexer_string(char *line, t_data *data);

t_cmd	*parser(t_token *token, t_data *data);
t_cmd	*ms_parser_cmdnew(t_token *token, size_t *idx, t_data *data);
char	**ms_parser_cmdnew_arg(t_token *token, size_t i_token);
size_t	ms_parser_cmdnew_fdsize(t_token *token, size_t idx, int type);
t_fd	*ms_parser_cmdnew_input(t_token *token, size_t i_token, t_data *data);
t_fd	*ms_parser_cmdnew_output(t_token *token, size_t i_token, t_data *data);

bool	ms_isenvchar(int c);
t_list	*ms_expand_envvar(char *line, size_t *pos, size_t len, t_data *data);
t_list	*ms_expand_envvar_dquote(char *line, size_t len, t_data *data);
char	*ms_getenv_val(char *env_key, t_data *data);
bool	ms_is_same_envkey(char *dest, char *src);
bool	ms_is_validenv(char *env_candidate);

void	ms_lexer_string_lstadd_back_substr(t_list **head, char *line, \
			size_t pos, size_t len);
char	*ms_lexer_string_lst_strjoin(t_list *head);

void	ms_setpath_home(char *path, char *arg, t_data *data);
void	ms_setpath_absolute(char *path, char *arg);
void	ms_setpath_relative(char *path, char *arg, t_data *data);

void	executer(t_cmd *cmd, t_data *data);
void	ms_exec_in_child_process(t_cmd *cmd, t_data *data);
void	ms_exec_a_builtin(t_cmd *cmd, int (*builtin)(char *arg[],
				t_data *data), t_data *data);

void	ms_fd_close(int fd[2]);
void	ms_fd_copy(int dest[2], int src[2]);
int		ms_fd_last_fd(t_fd *fd_lst);
void	ms_fd_close_all_cmd(t_cmd *cmd);
void	ms_init_fd(int fd[2]);
char	*ms_getpath_cmd(char *name, t_data *data);

int		(*ms_builtin_getfunc(char *arg))(char *argv[], t_data *data);
int		ms_builtin_cd(char *argv[], t_data *data);
int		ms_builtin_echo(char *argv[], t_data *data);
int		ms_builtin_env(char *argv[], t_data *data);
int		ms_builtin_exit(char *argv[], t_data *data);
int		ms_builtin_export(char *argv[], t_data *data);
void	ms_search_env_and_set(char *env_key, t_data *data, t_list *now);
int		ms_builtin_pwd(char *argv[], t_data *data);
int		ms_builtin_unset(char *argv[], t_data *data);

char	**ms_map_lst2map(t_list *lst);
void	*ms_map_clear(char **map, size_t size);
size_t	ms_map_size(char **map);

void	*free_and_return(void *malloc_obj);
void	*print_err_set_status_return_null(char *str, int status, \
			t_data *data);
void	*ms_clear_cmd_and_return_null(t_cmd *head);
bool	ms_is_directory(char *path);
char	*ft_strtrim_space(char const *s1);

t_list	*lstnew_env_ex(char *env_key);
void	ms_search_env_and_set(char *env_key, t_data *data, t_list *now);

#endif
