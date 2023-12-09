/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:11:30 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/27 22:07:39 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			ms_builtin_unset(char *argv[], t_data *data);
static void	ms_search_env_and_unset(char *env_key, t_data *data);

int	ms_builtin_unset(char *argv[], t_data *data)
{
	int	return_status;
	int	i;

	return_status = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ms_is_validenv(argv[i]) == false)
		{
			printf(MSG_INVAL_ID, "unset", argv[i++]);
			return_status = 1;
			continue ;
		}
		ms_search_env_and_unset(argv[i], data);
		i++;
	}
	return (return_status);
}

static void	ms_search_env_and_unset(char *env_key, t_data *data)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*tmp;

	cur = data->environ;
	prev = NULL;
	while (cur != NULL)
	{
		if (ms_is_same_envkey(cur->content, env_key))
		{
			if (prev == NULL)
				data->environ = cur->next;
			else
				prev->next = cur->next;
			tmp = cur->next;
			ft_lstdelone(cur, &free);
			cur = tmp;
			return ;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}
