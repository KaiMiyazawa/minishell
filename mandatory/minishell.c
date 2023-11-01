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

//エラー処理を込みでひと関数にしたreadline
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
		//bashは入力がから文字列の時は履歴に残らないので、以下の条件でadd_historyする
		if ()
			add_history(line);
		//入力にexitと入れるとプログラムを終われる
		if (!strcmp(line, "exit"))
		{
			free(line);
			break ;
		}
		//プログラム挙動中のsignal確認用
		else if (!strcmp(line, "./put_a_endless"))
			system("./put_a_endless");
		//ctrl + \ は、プログラム実行中は「Quit: 3\n」で終わらせないといけない
		//でもできてない←入力処理のわかっている問題の一つ
		else if (strlen(line) != 0)
		{
			//ここでlexer, perser, コマンド実行部に順次かけていく
			//すべてのデータの受け渡しは、data構造体を通して行う
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
