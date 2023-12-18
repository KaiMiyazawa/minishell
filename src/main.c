/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:18:15 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/17 16:19:22 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init(char *envp[], t_data *data);
static t_list	*tlst_from_strlst(char *envp[]);
static char		*readline_e(t_data *data);
static void		ms_clear_token(t_token *token);

int			g_signum;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	init(envp, &data);
	while (1)
	{
		data.line = readline_e(&data);
		if (data.line == NULL)
			break ;
		if (ft_strlen(data.line) == 0 && !free_and_return(data.line))
			continue ;
		if (*(data.line))
		{
			add_history(data.line);
			data.token = lexer(&data);
			data.cmd = parser(data.token, &data);
			executer(data.cmd, &data);
			ms_clear_token(data.token);
		}
		free(data.line);
		data.line = NULL;
	}
	ms_builtin_exit(NULL, &data);
	return (data.status);
}

static void	init(char *envp[], t_data *data)
{
	data->environ = tlst_from_strlst(envp);
	data->status = 0;
	data->cmd = NULL;
	g_signum = -1;
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

static char	*readline_e(t_data *data)
{
	char	*line;
	char	*result;

	sigset_rl();
	sigset_noquit();
	rl_done = 0;
	rl_event_hook = NULL;
	line = readline(PROMPT_MINISH);
	if (line == NULL)
		result = NULL;
	else if (ft_strlen(line) == 0)
		result = ft_strdup("");
	else
		result = ft_strtrim(line, " \t");
	free(line);
	line = NULL;
	if (g_signum == SIGINT)
		data->status = 1;
	g_signum = -1;
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
		token[i].str = NULL;
		i++;
	}
	free(token);
	token = NULL;
}
