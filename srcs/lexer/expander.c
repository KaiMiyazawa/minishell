/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:01:38 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/26 22:40:35 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//list1->list2->list3
//list2->list3
void	delete_a_list(t_tk_list *tk_list)
{
	t_tk_list	*tmp;

	tmp = tk_list->next;
	if (tmp == NULL)
	{
		free(tk_list->word);
		tk_list->word = NULL;
		return ;
	}
	tk_list->type = tk_list->next->type;
	free(tk_list->word);
	tk_list->word = tk_list->next->word;
	tk_list->next = tk_list->next->next;
	tmp->word = NULL;
	tmp->next = NULL;
	free(tmp);
	return ;
}

char	*tk_strjoin_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

char	*get_env_value(char *env_key, t_data *data)
{
	char	*env_value;

	if (env_key[0] == '?')
		return (ft_itoa(data->pid));
	else if (ft_isdigit(env_key[0]))
		return (ft_strdup(env_key + 1));
	else
	{
		env_value = getenv(env_key);
		if (env_value == NULL)
			return (ft_strdup(""));
		else
			return (ft_strdup(env_value));
	}
}

//DOLL -> STR -> ?(maybe NULL)
//		 (DOLL)
//                                DOLL
void	expand_dollar(t_tk_list *tk_list, t_data *data)
{
	t_tk_list	*tmp;
	char		*env_value;

	tmp = tk_list->next;
	env_value = NULL;
	if (tmp->type == STR)
		env_value = get_env_value(tmp->word, data);
	else if (tmp->type == DOLL)
		env_value = ft_strdup("$");
	if (env_value == NULL)
		put_error_destroy_data_exit(data, "malloc error", 12);
	free(tmp->word);
	tmp->word = env_value;
	tmp->type = STR;
	delete_a_list(tk_list);
}

void	expand_quotes(t_tk_list *tk_list, t_data *data, bool dq_flag)
{
	t_tk_list	*tmp;
	t_tk_type	quate;

	quate = tk_list->type;
	tmp = tk_list->next;
	tk_list->type = STR;
	free(tk_list->word);
	tk_list->word = ft_strdup("");
	if (tk_list->word == NULL)
		put_error_destroy_data_exit(data, "malloc error", 12);
	while (tmp->type != quate)
	{
		if (dq_flag && tmp->type == DOLL && (tmp->next->type == STR
				|| tmp->next->type == DOLL))
		{
			expand_dollar(tmp, data);
			continue ;
		}
		tk_list->word = tk_strjoin_free(tk_list->word, tmp->word);
		if (tk_list->word == NULL)
			put_error_destroy_data_exit(data, "malloc error", 12);
		delete_a_list(tmp);
	}
	if (tmp->next != NULL)
		delete_a_list(tmp);
	else
	{
		free(tmp->word);
		tmp->word = NULL;
		free(tmp);
		tk_list->next = NULL;
	}
}

void	expander(t_data *data)
{
	t_tk_list	*tmp;
	t_tk_list	*tmp2;

	tmp = data->tk_head;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->type == SQUOTE)
			expand_quotes(tmp, data, 0);
		else if (tmp->type == DQUOTE)
			expand_quotes(tmp, data, 1);
		else if (tmp->type == DOLL && (tmp->next->type == STR
				|| tmp->next->type == DOLL))
		{
			expand_dollar(tmp, data);
			continue ;
		}
		tmp = tmp->next;
	}
	tmp = data->tk_head;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->type == STR && tmp->next->type == STR)
		{
			tmp->word = tk_strjoin_free(tmp->word, tmp->next->word);
			if (tmp->word == NULL)
				put_error_destroy_data_exit(data, "malloc error", 12);
			free(tmp->next->word);
			tmp2 = tmp->next->next;
			free(tmp->next);
			tmp->next = tmp2;
			continue ;
		}
		tmp = tmp->next;
	}
	tmp = data->tk_head;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->type == SPACE_)
		{
			delete_a_list(tmp);
			continue ;
		}
		tmp = tmp->next;
	}
}
