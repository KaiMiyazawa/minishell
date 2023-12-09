/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:18:15 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:51:19 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init(char *envp[], t_data *data);
static t_list	*tlst_from_strlst(char *envp[]);
static char		*readline_e(void);
static void		ms_clear_token(t_token *token);

t_shell		g_shell;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	init(envp, &data);
	while (1)
	{
		data.line = readline_e();
		if (data.line == NULL)
			break ;
		if (*(data.line))
		{
			add_history(data.line);
			data.token = lexer(&data);
			g_shell.cmd = parser(data.token, &data);
			sigset_exec();
			executer(g_shell.cmd, &data);
			ms_clear_token(data.token);
		}
		free(data.line);
	}
	ms_builtin_exit(NULL, &data);
	return (g_shell.status);
}

static void	init(char *envp[], t_data *data)
{
	data->environ = tlst_from_strlst(envp);
	g_shell.status = 0;
	g_shell.cmd = NULL;
	g_shell.kill_child = false;
	g_shell.heredoc_sigint = false;
	data->now_cmd = NULL;
}

static t_list	*tlst_from_strlst(char *envp[])
{
	t_list	head;
	t_list	*now;
	char	*content;
	size_t	i;

	head.next = NULL;
	now = &head;
	i = 0;
	while (envp[i] != NULL)
	{
		content = ft_strdup(envp[i]);
		if (content == NULL)
			exit(EXIT_FAILURE);
		now->next = ft_lstnew(content);
		if (now->next == NULL)
			exit(EXIT_FAILURE);
		now = now->next;
		i++;
	}
	return (head.next);
}

static char	*readline_e(void)
{
	char	*line;
	char	*result;

	sigset_rl();
	sigset_noquit();
	rl_done = 0;
	rl_event_hook = NULL;
	line = readline(PROMPT_MINISH);
	result = ft_strtrim_space(line);
	free(line);
	return (result);
}

static void	ms_clear_token(t_token *token)
{
	size_t	i;

	if (token == NULL)
		return ;
	i = 0;
	while (&token[i] && token[i].str)
	{
		free(token[i].str);
		i++;
	}
	free(token);
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q minishell");
// }
