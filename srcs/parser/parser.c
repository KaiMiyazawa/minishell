/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:43:47 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/29 22:08:42 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*print_err_set_status_return_null(char *str, int status, t_data *data)
{
	if (str != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
	}
	if (status >= 0)
		data->status = status;
	return (NULL);
}

static bool	get_heredoc_txt(const char *eof, int fd, t_data *data)
{
	char	*buf;

	ms_sigset_rl_heredoc();
	//rl_event_hook = is_heredoc_sigint;
	while (g_sig_num != SIGINT)
	{
		buf = readline("here_doc> ");
		if (!buf)
			return (true);
		if (ft_strncmp(buf, eof, INT_MAX) == 0)
		{
			free(buf);
			return (true);
		}
		ft_putendl_fd(buf, fd);
		free(buf);
	}
	if (data)
		;
	return (false);
}

static int	get_heredoc_pipe(const char *eof, t_data *data)
{
	int	fd[2];

	pipe(fd);
	if (get_heredoc_txt(eof, fd[1], data) == true)
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

size_t	ms_parser_cmdnew_fdsize(t_tk *token, size_t idx, t_tk_type f1, t_tk_type f2)
{
	ssize_t	size;

	size = 0;
	while (token[idx].word != NULL && token[idx].type != PIPE)
	{
		if (token[idx].type == f1)
		{
			idx++;
			if (token[idx++].type != STR)
				return (-1);
			size++;
		}
		else if (token[idx++].type == f2)
		{
			if (token[idx++].type != STR)
				return (-1);
			size++;
		}
	}
	return (size);
}

static bool	ms_parser_input_sub(t_fd *input, t_tk *token, size_t *i_token, t_data *data)
{
	ssize_t	i_input;

	i_input = 0;
	while (token[*i_token].word != NULL && token[*i_token].type != PIPE)
	{
		if (token[*i_token].type == LDIR || token[*i_token].type == LLDIR)
		{
			if (token[*i_token].type == LLDIR)
				input[i_input].fd = get_heredoc_pipe(
						token[++(*i_token)].word, data);
			else
				input[i_input].fd = open(token[++(*i_token)].word, O_RDONLY);
			if (input[i_input].fd < 0)
				return (false);
			input[i_input++].path = token[*i_token].word;
		}
		(*i_token)++;
	}
	input[i_input].path = NULL;
	input[i_input].fd = -1;
	return (true);
}

t_fd	*ms_parser_cmdnew_input(t_tk *token, size_t i_token, t_data *data)
{
	t_fd	*input;
	ssize_t	size;

	size = ms_parser_cmdnew_fdsize(token, i_token, LDIR, LLDIR);
	if (size == -1)
		return (print_err_set_status_return_null(\
				MSG_SYNTAX_ERR, 2, data));
	input = (t_fd *)ft_calloc_e((size + 1), sizeof(t_fd), data);
	here_debug();
	errno = 0;
	if (ms_parser_input_sub(input, token, &i_token, data) == false)
	{
		free(input);
		if (errno == 0)
		{
			if (data->heredoc_sigint == false)
				data->status = 0;
			return (NULL);
		}
		return (print_err_set_status_return_null(\
				strerror(errno), 1, data));
	}
	return (input);
}


static bool	ms_parser_output_sub(t_fd *output, t_tk *token, size_t *i_token)
{
	ssize_t	i_output;

	i_output = 0;
	while (token[*i_token].word != NULL && token[*i_token].type != PIPE)
	{
		if ((token[*i_token].type == RDIR || token[*i_token].type == RRDIR))
		{
			if (token[*i_token].type == RRDIR)
				output[i_output].fd = open(token[++(*i_token)].word, \
										O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				output[i_output].fd = open(token[++(*i_token)].word, \
										O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (output[i_output].fd < 0)
				return (false);
			output[i_output++].path = token[*i_token].word;
		}
		(*i_token)++;
	}
	output[i_output].path = NULL;
	output[i_output].fd = -1;
	return (true);
}

t_fd	*ms_parser_cmdnew_output(t_tk *token, size_t i_token, t_data *data)
{
	t_fd	*output;
	ssize_t	size;

	size = ms_parser_cmdnew_fdsize(token, i_token, RDIR, RRDIR);
	if (size == -1)
		return (print_err_set_status_return_null(\
				MSG_SYNTAX_ERR, 2, data));
	output = (t_fd *)malloc((size + 1) * sizeof(t_fd));
	if (output == NULL)
		exit(EXIT_FAILURE);
	if (ms_parser_output_sub(output, token, &i_token) == false)
	{
		free(output);
		return (print_err_set_status_return_null(\
				strerror(errno), 1, data));
	}
	return (output);
}
















t_cmd	*ps_cmdnew(t_data *data, size_t *idx)
{
	t_cmd	*cmd;
	t_tk	*token;

	token = data->tk;
	if (token == NULL || token[*idx].word == NULL)
		return (NULL);
	cmd = (t_cmd *)ft_calloc_e(1, sizeof(t_cmd), data);
	if (cmd == NULL)
		return (NULL);
	cmd->input = ms_parser_cmdnew_input(token, *idx, data);
	if (cmd->input == NULL)
		return (NULL);
	cmd->output = ms_parser_cmdnew_output(token, *idx, data);
	if (cmd->output == NULL)
		return (NULL);
	cmd->arg = ms_parser_cmdnew_arg(token, *idx, data);
	if (cmd->arg == NULL)
		return (NULL);
	cmd->path = ms_getpath_cmd(cmd->arg[0], data);
	if (cmd->path == NULL)
		return (NULL);
	while (token[*idx].word != NULL && token[*idx].type != PIPE)
		(*idx)++;
	return (cmd);
}

static bool	ps_check_pipe_error(t_tk *token, int last)
{
	if (token[0].type == PIPE)
		return (false);
	if (token[last].type == PIPE)
		return (false);
	return (true);
}

bool	parser(t_data *data)
{
	size_t	idx;
	t_cmd	*head;
	t_cmd	*cur;

	data->heredoc_sigint = false;
	if (ps_check_pipe_error(data->tk, data->tk_size) == false)
		return (put_error_destroy_data_continue(data,
				"syntax error", 258));
	idx = 0;
	head = ps_cmdnew(data, &idx);
	if (head == NULL)
		return (put_error_destroy_data_continue(data,
				NULL, -1));
	cur = head;
	while (data->tk[idx++].type == PIPE)
	{
		cur->next = ps_cmdnew(data, &idx);
		if (cur->next == NULL)
			return (put_error_destroy_data_continue(data,
					NULL, -1));
		cur->next->prev = cur;
		cur = cur->next;
	}
	data->cmd = head;
	return (true);
}
