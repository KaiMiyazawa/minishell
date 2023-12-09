/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 22:25:40 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/27 22:53:31 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*readline_e(char *prompt)
{
	char	*line;
	char	*result;


	line = NULL;
	ms_sigset_rl();
	ms_sigset_noquit();
	rl_done = 0;
	rl_event_hook = NULL;
	line = readline(prompt);
	result = ft_strtrim(line, SPACE_AND_TAB);
	free(line);
	return (result);
}

void	exit_minishell(int exit_status, t_data *data)
{
	printf("exit\n");
	if (data != NULL)
		free_all_data(data, 1);
	data->status = exit_status;
	exit(data->status);
}

bool	is_unclosed_quotes(char *line)
{
	int	count;
	int	state;

	count = 0;
	state = 0;
	while (line[count] != '\0')
	{
		if (state == 0 && line[count] == '\'')
			state = -1;
		else if (state == 0 && line[count] == '\"')
			state = 1;
		else if (state == -1 && line[count] == '\'')
			state = 0;
		else if (state == 1 && line[count] == '\"')
			state = 0;
		count++;
	}
	if (state == 0)
		return (false);
	else
	{
		ft_putendl_fd("minishell: unclosed quote", STDERR_FILENO);
		return (true);
	}
}

bool	check_validity(t_data *data, char *line)
{
	bool	validity;

	validity = true;
	if (line == NULL)
		exit_minishell(EXIT_SUCCESS, data);
	if (line[0] == '\0')
		validity = false;
	else if (is_unclosed_quotes(line) == true)
		validity = false;
	if (validity == false)
		free(line);
	return (validity);
}

void	minishell(t_data *data)
{
	char	*line;

	line = NULL;
	while (data->status == 0)
	{
		//handle_signals_rl();
		line = readline_e(PROMPT);
		if (!check_validity(data, line))
			continue ;
		add_history(line);
		data->line_size = ft_strlen(line);
		data->line = line;
		lexer(data, line);
		if (DEBUG)
		{
			confirm_tklist(data);
			confirm_tk(data);
		}
		if (!parser(data))
			continue ;
		if (!strcmp(line, "exit"))
			break ;
		ms_sigset_exec();
		executer(data);
		free_all_data(data, 0);
	}
}
