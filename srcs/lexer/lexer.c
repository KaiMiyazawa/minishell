/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:36:08 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/27 11:39:44 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	tk_trim_d_dir(t_tk_list *tk_list, t_tk_type type, t_data *data)
{
	t_tk_list	*tmp;

	tk_list->type = type;
	tmp = tk_list->next;
	tk_list->next = tmp->next;
	free(tmp->word);
	free(tmp);
	free(tk_list->word);
	tk_list->word = (char *)ft_calloc_e(sizeof(char), 3, data);
	if (type == RRDIR)
		ft_strlcpy(tk_list->word, ">>", 3);
	else
		ft_strlcpy(tk_list->word, "<<", 3);
	return ;
}

static bool	tk_is_num(char *word)
{
	int	count;

	count = 0;
	while (word[count] != '\0')
	{
		if (word[count] < '0' || word[count] > '9')
			return (false);
		count++;
	}
	return (true);
}

static void	tk_trim_tklist(t_data *data)
{
	t_tk_list		*tmp;

	tmp = data->tk_head;
	while (tmp->next != NULL)
	{
		if (tmp->type == RDIR && tmp->next->type == RDIR)
			tk_trim_d_dir(tmp, RRDIR, data);
		else if (tmp->type == LDIR && tmp->next->type == LDIR)
			tk_trim_d_dir(tmp, LLDIR, data);
		else if (tmp->type == STR && tk_is_num(tmp->word)
			&& (tmp->next->type == RDIR || tmp->next->type == LDIR))
			tmp->type = RINT;
		if (tmp->next != NULL)
			tmp = tmp->next;
	}
}

void	tk_comvert_tklist_to_tk(t_data *data)
{
	t_tk_list	*tmp;
	int			i;

	tmp = data->tk_head;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	data->tk_size = i;
	data->tk = (t_tk *)ft_calloc_e(sizeof(t_tk), (i + 1), data);
	tmp = data->tk_head;
	i = 0;
	while (tmp != NULL)
	{
		data->tk[i].word = (char *)ft_calloc_e(sizeof(char),
				(ft_strlen(tmp->word) + 1), data);
		ft_strlcpy(data->tk[i].word, tmp->word, ft_strlen(tmp->word) + 1);
		data->tk[i].type = tmp->type;
		i++;
		tmp = tmp->next;
	}
	data->tk[i].type = NULL_;
	data->tk[i].word = NULL;
}

void	lexer(t_data *data, char *line)
{
	t_tk_type	tmp_type;
	int			count;

	count = 0;
	//data->line_size = ft_strlen(line);
	//data->line = line;
	while (line[count])
	{
		tmp_type = tk_get_tktype(line[count]);
		if (!tk_list_add_back(data, tk_list_new(tk_make_word(
						line + count, tmp_type), tmp_type)))
			put_error_destroy_data_exit(data, "malloc error", 12);
		count += ft_strlen(data->tk_tail->word);
	}
	tk_trim_tklist(data);
	expander(data);
	tk_comvert_tklist_to_tk(data);
}
