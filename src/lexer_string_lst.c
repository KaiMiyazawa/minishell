/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:15:58 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:21:04 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lexer_string_lstadd_back_substr(t_list **head, char *line, \
	size_t pos, size_t len)
{
	char	*substr;

	substr = ft_substr(line, pos, len);
	if (substr == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(head, ft_lstnew(substr));
	return ;
}

char	*ms_lexer_string_lst_strjoin(t_list *head)
{
	size_t	joined_str_size;
	char	*joined_str;
	t_list	*now;

	joined_str_size = 0;
	now = head;
	while (now != NULL)
	{
		if (now->content != NULL)
			joined_str_size += ft_strlen(now->content);
		now = now->next;
	}
	joined_str = ft_calloc(joined_str_size + 1, sizeof(char));
	if (joined_str == NULL)
		exit(EXIT_FAILURE);
	now = head;
	while (now != NULL)
	{
		if (now->content != NULL)
			ft_strlcat(joined_str, now->content, joined_str_size + 1);
		now = now->next;
	}
	return (joined_str);
}
