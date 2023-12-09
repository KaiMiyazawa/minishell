/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:26:22 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/25 16:45:55 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	here_debug(void)
{
	printf("here\n");
}

//スムーズな開発のためにdata構造体の中身を一覧する関数
void	confirm_data(t_data *data)
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


void	confirm_tklist(t_data *data)
{
	//以下、トークン一覧のためのパート
	//最後は消す
	t_tk	*tmp = data->tk_head;
	int		c = 0;
	const char	*type_name[] = {"STR", "RDIR", "RRDIR", "LDIR",
		"LLDIR", "SPACE_", "SQUOTE", "DQUOTE", "PIPE", "DOLL", "RINT",};
	while (tmp->next != NULL)
	{
		printf("[%d] %s %s$\n",++c,type_name[tmp->type],tmp->word);
		tmp = tmp->next;
	}
	printf("[%d] %s %s$\n",++c,type_name[tmp->type],tmp->word);
	if (tmp->next == NULL)
		printf("[%d] NULL %p$\n",++c,tmp->next);
	//ここまで
}

	//killコマンドでctrl+Cとかの挙動確認する用
void	put_pid(void)
{
	pid_t				pid;

	pid = getpid();
	printf("%d\n", pid);//プロセス番号の確認
	return ;
}
