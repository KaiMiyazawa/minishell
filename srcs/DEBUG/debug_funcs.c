/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:27:37 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/29 22:10:11 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_debug(void)
{
	printf("here\n");
}

//スムーズな開発のためにdata構造体の中身を一覧する関数
void	confirm_data(t_data *data)
{
	//int	b;
	int	c;

	printf("====data====\n");
	//printf("\n[[envp]]\n");
	//b = -1;
	//while (data->envp[++b])
	//	printf(" %d : %s\t", b, data->envp[b]);
	//printf(" %d : %s\n", b, data->envp[b]);
	c = 0;
	printf("\n[[path]]\n");
	while (data->path[c])
		printf("%s\n", data->path[c++]);
	printf("====/data====\n");
}

//tklistを確認するための関数
void	confirm_tklist(t_data *data)
{
	//以下、トークン一覧のためのパート
	//最後は消す
	t_tk_list	*tmp = data->tk_head;
	int		c = 0;
	const char	*type_name[] = {"NONE", "STR", "RDIR", "RRDIR", "LDIR",
		"LLDIR", "SPACE_", "SQUOTE", "SQ_STR", "DQUOTE", "DQ_STR",
		"PIPE", "DOLL", "RINT", "NULL_"};
	while (tmp->next != NULL)
	{
		printf("[%d] %s %s\n",++c,type_name[tmp->type],tmp->word);
		tmp = tmp->next;
	}
	printf("[%d] %s %s\n",++c,type_name[tmp->type],tmp->word);
	if (tmp->next == NULL)
		printf("[%d] NULL %p\n",++c,tmp->next);
	//ここまで
}

//tkを確認するための関数
void	confirm_tk(t_data *data)
{
	int			count = -1;
	const char	*type_name[] = {"NONE", "STR", "RDIR", "RRDIR", "LDIR",
		"LLDIR", "SPACE_", "SQUOTE", "SQ_STR", "DQUOTE", "DQ_STR",
		"PIPE", "DOLL", "RINT", "NULL_"};

	while (++count < data->tk_size + 1)
		printf("[%d]type:%s str:%s\n", count,
			type_name[data->tk[count].type], data->tk[count].word);
}
