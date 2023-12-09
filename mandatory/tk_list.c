/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:04:15 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/18 14:54:34 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

t_tk	*tk_list_new(char *word, t_tk_type type)
{
	t_tk	*new;

	new = (t_tk *)malloc(sizeof(t_tk));
	if (!new)
		return (NULL);
	new->word = word;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	tk_list_add_back(t_data *data, t_tk *new)
{
	if (data->tk_head == NULL)
	{
		data->tk_head = new;
		data->tk_tail = new;
		data->tk_tail->next = NULL;
		return ;
	}
	data->tk_tail->next = new;
	data->tk_tail = new;
	new->next = NULL;
	return ;
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
		result = (char *)malloc(sizeof(char) * (count + 1));
		strlcpy(result, line, count + 1);
	}
	else
	{
		result = (char *)malloc(2 * sizeof(char));
		result[0] = line[0];
		result[1] = '\0';
	}
	return (result);
}
