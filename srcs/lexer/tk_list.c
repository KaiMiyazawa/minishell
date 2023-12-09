/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:04:15 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/27 11:30:29 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tk_list	*tk_list_new(char *word, t_tk_type type)
{
	t_tk_list	*new;

	if (word == NULL)
		return (NULL);
	new = (t_tk_list *)ft_calloc(sizeof(t_tk_list), 1);
	if (!new)
		return (NULL);
	new->word = word;
	new->type = type;
	new->next = NULL;
	return (new);
}

bool	tk_list_add_back(t_data *data, t_tk_list *new)
{
	if (new == NULL)
		return (false);
	if (data->tk_head == NULL)
	{
		data->tk_head = new;
		data->tk_tail = new;
		data->tk_tail->next = NULL;
		return (true);
	}
	data->tk_tail->next = new;
	data->tk_tail = new;
	new->next = NULL;
	return (true);
}

static int	tk_count_word_len(char *line, t_tk_type type)
{
	int	count;

	count = 0;
	while (line[count] && tk_get_tktype(line[count]) == type)
		count++;
	return (count);
}

char	*tk_make_word(char *line, t_tk_type type)
{
	int		count;
	char	*result;

	if (type == STR || type == SPACE_)
	{
		count = tk_count_word_len(line, type);
		result = (char *)ft_calloc(sizeof(char), (count + 1));
		if (result == NULL)
			return (NULL);
		strlcpy(result, line, count + 1);
	}
	else
	{
		result = (char *)ft_calloc(2, sizeof(char));
		if (result == NULL)
			return (NULL);
		result[0] = line[0];
		result[1] = '\0';
	}
	return (result);
}
