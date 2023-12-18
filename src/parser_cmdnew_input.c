/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmdnew_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:21:30 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/17 15:51:19 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ms_parser_input_sub(t_fd *input, t_token *token, size_t *i_token, \
		t_data *data);
static int	get_heredoc_pipe(const char *eof, t_data *data);
static int	is_heredoc_sigint(void);
static bool	get_heredoc_txt(const char *eof, int fd, t_data *data);

t_fd	*ms_parser_cmdnew_input(t_token *token, size_t i_token, t_data *data)
{
	t_fd	*input;
	ssize_t	size;

	size = ms_parser_cmdnew_fdsize(token, i_token, TYPE_IN);
	if (size == -1)
		return (print_err_set_status_return_null(\
				MSG_SYNTAX_ERR, 258, data));
	input = (t_fd *)ft_calloc((size + 1), sizeof(t_fd));
	if (input == NULL)
		exit(EXIT_FAILURE);
	errno = 0;
	if (ms_parser_input_sub(input, token, &i_token, data) == false)
	{
		free(input);
		input = NULL;
		if (errno == 0)
		{
			if (g_signum != SIGINT)
				data->status = 0;
			return (NULL);
		}
		return (print_err_set_status_return_null(\
				strerror(errno), 1, data));
	}
	return (input);
}

static bool	ms_parser_input_sub(t_fd *input, t_token *token, size_t *i_token, \
		t_data *data)
{
	ssize_t	i_input;

	i_input = 0;
	while (token[*i_token].str != NULL && token[*i_token].type != TYPE_PIPE)
	{
		if ((token[*i_token].type & TYPE_IN) == TYPE_IN)
		{
			if (token[*i_token].type == TYPE_HEREDOC)
				input[i_input].fd = get_heredoc_pipe(token[++(*i_token)].str, \
					data);
			else
				input[i_input].fd = open(token[++(*i_token)].str, O_RDONLY);
			if (input[i_input].fd < 0)
				return (false);
			input[i_input++].path = token[*i_token].str;
		}
		(*i_token)++;
	}
	input[i_input].path = NULL;
	input[i_input].fd = -1;
	return (true);
}

static int	get_heredoc_pipe(const char *eof, t_data *data)
{
	int	fd[2];

	pipe(fd);
	if (get_heredoc_txt(eof, fd[1], data))
	{
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		ms_fd_close(fd);
		return (-1);
	}
}

static int	is_heredoc_sigint(void)
{
	if (g_signum == SIGINT)
		rl_done = 1;
	return (0);
}

static bool	get_heredoc_txt(const char *eof, int fd, t_data *data)
{
	char	*buffer;

	sigset_rl_heredoc();
	rl_event_hook = is_heredoc_sigint;
	while (g_signum != SIGINT)
	{
		buffer = readline(PROMPT_HREDOC);
		if (!buffer)
			return (true);
		if (ft_strncmp(buffer, eof, INT_MAX) == 0)
		{
			free(buffer);
			buffer = NULL;
			return (true);
		}
		ft_putendl_fd(buffer, fd);
		free(buffer);
		buffer = NULL;
	}
	if (g_signum == SIGINT)
		data->status = 1;
	g_signum = -1;
	return (false);
}
