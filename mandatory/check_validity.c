/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:50:57 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/18 18:52:46 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

//state 0: in string
//state -1: in single quote
//state 1: in double quote
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

bool	check_validity(char *line, t_data *data)
{
	bool	validity;

	validity = true;
	if (line == NULL)
	{
		free(line);
		exit_minishell(EXIT_SUCCESS, data);
	}
	if (line[0] == '\0')
		validity = false;
	else if (is_unclosed_quotes(line) == true)
		validity = false;
	if (validity == false)
		free(line);
	return (validity);
}
