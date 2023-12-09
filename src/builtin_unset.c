/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:11:30 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:09:00 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_search_env_and_unset(char *env_key, t_data *data);

int	ms_builtin_unset(char *argv[], t_data *data)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ms_is_validenv(argv[i]) == false)
		{
			ft_putendl_fd(MSG_INVAL_ID, STDERR_FILENO);
			i++;
			status = 1;
			continue ;
		}
		ms_search_env_and_unset(argv[i], data);
		i++;
	}
	return (status);
}

static void	ms_search_env_and_unset(char *env_key, t_data *data)
{
	t_list	*now;
	t_list	*prev;
	t_list	*tmp;

	now = data->environ;
	prev = NULL;
	while (now != NULL)
	{
		if (ms_is_same_envkey(now->content, env_key))
		{
			if (prev == NULL)
				data->environ = now->next;
			else
				prev->next = now->next;
			tmp = now->next;
			ft_lstdelone(now, &free);
			now = tmp;
			return ;
		}
		else
		{
			prev = now;
			now = now->next;
		}
	}
}
