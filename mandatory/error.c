/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:44:49 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/29 18:45:06 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_str(char *s1, char *s2)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (s1[count] != '\0')
		count++;
	while (s2[count2] != '\0')
		s1[count++] = s2[count2++];
	s1[count] = '\0';
}

//bashの形式に合わせたエラーメッセージを出して、グローバル変数g_stateに修了ステータスを格納する関数です。
//エラーメッセージの具体例↓
//minishell: pwdd: command not found
void	print_error(char *error_msg, char *addition, bool exit_state, t_data *d)
{
	char	*error;
	int		size;

	size = 11 + ft_strlen(error_msg) + 1 + 1;
	if (addition != NULL)
		size += 2 + ft_strlen(addition);
	error = (char *)ft_calloc(sizeof(char), size);
	if (!error)
		perror(strerror(errno));
	ft_strlcpy(error, "minishell: ", 12);
	if (addition != NULL)
	{
		add_str(error, addition);
		add_str(error, ": ");
	}
	add_str(error, error_msg);
	add_str(error, "\n");
	if (write(2, error, size) == FAILED)
		perror(strerror(errno));
	free(error);
	g_state = exit_state;
}

