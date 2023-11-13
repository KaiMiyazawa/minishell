/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:08:46 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/11/07 11:48:06 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

//スムーズな開発のためにdata構造体の中身を一覧する関数
static void	confirm_data(t_data *data)
{
	printf("====data====\n");
	printf("[ac]:%d\n[[av]]\n", data->ac);
	int a = -1;
	while (data->av[++a])
		printf("%d : %s\n", a, data->av[a]);
	printf("\n[[envp]]\n");
	int b = -1;
	while (data->envp[++b])
		printf(" %d : %s ", b, data->envp[b]);
	printf(" %d : %s \n", b, data->envp[b]);
	printf("\n[in_fd] : %d\n[out_fd] : %d\n", data->in_fd, data->out_fd);
	int c =0;
	printf("\n[[path]]\n");
	while (data->path[c])
	{
		printf("%s\n", data->path[c]);
		c++;
	}
	printf("====/data====\n");
}

//最初に、dataに設定できる変数を設定する関数data_init
static void	data_init(int ac, char **av, char **ev, t_data *data)
{
	g_state = 0;
	data->ac = ac;
	data->av = av;
	data->envp = ev;
	data->in_fd = STDIN_FILENO;
	data->out_fd = STDOUT_FILENO;

	data->path = make_path(getenv("PATH"));
	if (data->path == NULL)
		exit(1);
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
	}
	else
	{
		printf("do not pass argments\n");
		exit(1);
	}
	return (0);
}

//__attribute__((destructor))
//static void destructor() {
//	system("leaks -q a.out");
//}
