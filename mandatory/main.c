/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:08:46 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/11/18 19:32:43 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

//最初に、dataに設定できる変数を設定する関数data_init
static void	data_init(int ac, char **av, char **ev, t_data *data)
{
	g_state = 0;
	data->ac = ac;
	data->av = av;
	data->envp = ev;

	data->path = make_path(getenv("PATH"));
	if (data->path == NULL)
		exit(1);

	data->tk_head = NULL;
	data->tk_tail = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	//諸々の必要な変数を子供にもつ構造体data
	t_data	data;

	if (argc == 1)
	{
		data_init(argc, argv, envp, &data);
		//confirm_data()は、開発をスムーズにするための関数。dataを一覧する。
		confirm_data(&data);
		minishell(&data);
		free_all_data(&data);
	}
	else
	{
		printf("do not pass argments\n");
		exit(1);
	}
	return (0);
}

__attribute__((destructor))
static void destructor() {
	system("leaks -q minishell");
}
