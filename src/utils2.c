/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:19:15 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/13 16:20:42 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*lstnew_env_ex(char *env_key)
{
	t_list	*new;

	new = ft_lstnew(ft_strdup(env_key));
	if (new == NULL || new->content == NULL)
		exit(EXIT_FAILURE);
	return (new);
}

static t_list	*ms_lstnew_env(char *env_key)
{
	t_list	*new;

	env_key[ft_strlen(env_key)] = '=';
	new = ft_lstnew(ft_strdup(env_key));
	if (new == NULL || new->content == NULL)
		exit(EXIT_FAILURE);
	return (new);
}

void	ms_search_env_and_set(char *env_key, t_data *data, t_list *now)
{
	t_list	*prev;
	t_list	*new;

	prev = NULL;
	while (now != NULL)
	{
		if (ms_is_same_envkey(now->content, env_key))
		{
			free(now->content);
			now->content = NULL;
			env_key[ft_strlen(env_key)] = '=';
			now->content = ft_strdup(env_key);
			if (now->content == NULL)
				exit(EXIT_FAILURE);
			return ;
		}
		prev = now;
		now = now->next;
	}
	new = ms_lstnew_env(env_key);
	if (prev == NULL)
		data->environ = new;
	else
		prev->next = new;
}
