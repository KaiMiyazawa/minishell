/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:44:49 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/18 18:53:09 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//bashの形式に合わせたエラーメッセージを出して、グローバル変数g_stateに修了ステータスを格納する関数です。
//エラーメッセージの具体例↓
//minishell: pwdd: command not found
void	print_error(char *error_msg, char *addition, int exit_state)
{
	if (error_msg == NULL)
		return ;
	printf("minishell: ");
	if (addition != NULL)
		printf("%s: ", addition);
	printf("%s\n", error_msg);
	g_state = exit_state;
}

//void	fatal_error()
//{
//	print_error("fatal error", NULL, 1);
//	exit(g_state);
//}

void	put_unexpected_token_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	g_state = 258;
}

void	exit_minishell(int exit_status, t_data *data)
{
	printf("exit\n");
	g_state = exit_status;
	if (data)
		free_all_data(data);
	exit(exit_status);
}
