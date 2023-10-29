/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:31:59 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/18 17:20:50 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

char	*readline_e(char *prompt)
{
	char	*line;

	line = NULL;
	line = readline(prompt);
	if (line == NULL)
	{
		printf(" EOF\nexit\n");
		exit(1);
	}
	return (line);
}

void	minishell(t_data *data)
{
	char				*line;

	//killコマンドでctrl+Cとかの挙動確認する用
	pid_t				pid;
	pid = getpid();
	printf("%d\n", pid);//プロセス番号の確認

	line = NULL;
	handle_signals();
	while (1)
	{
		line = readline_e("> ");
		if (ft_strlen(line) > 0)
			add_history(line);
		if (!strcmp(line, "exit"))
		{
			free(line);
			break ;
		}
		//プログラム挙動中のsignal確認用
		else if (!strcmp(line, "./put_a_endless"))
			system("./put_a_endless");
		//ctrl + \ は、プログラム実行中は「Quit: 3\n」で終わらせないといけない
		//でもできてない
		else if (strlen(line) != 0)
		{
			printf("command : %s\n", line);
			lexer(line, data);
			perser(data);
			evaluater(data);
		}
		free(line);
		line = NULL;
	}
	printf("exit\n");
}
