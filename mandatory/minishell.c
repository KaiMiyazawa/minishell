/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:31:59 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/25 16:14:25 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

//エラー処理を込みでひと関数にしたreadline
static char	*readline_e(char *prompt)
{
	char	*line;
	char	*result;

	rl_outstream = stderr;
	line = NULL;
	line = readline(prompt);
	//文頭と文末のSPACEと\tをトリミングします。
	result = ft_strtrim(line, SPACE_AND_TAB);
	free(line);
	return (result);
}

void	minishell(t_data *data)
{
	char				*line;

	if (DEBUG)
		put_pid();
	handle_signals();
	while (1)
	{
		line = readline_e("> ");
		if (!strcmp(line, "exit"))
		{
			free(line);
			break ;
		}
		else if (!strcmp(line, "./put_a_endless"))
			system("./put_a_endless");
		else
		{
			add_history(line);
			lexer(line, data);
			confirm_tklist(data);
			perser(data);
			expander(data);
			executor(data);
			tk_free_list(data);
		}
		free(line);
		line = NULL;
	}
	printf("exit\n");
}
