/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:11:44 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/13 15:26:57 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_getenv_line(char *env_key, t_data *data);

char	*ms_getenv_val(char *env_key, t_data *data)
{
	char	*env_line;

	env_line = ms_getenv_line(env_key, data);
	if (env_line == NULL)
		return (NULL);
	return (ft_strchr(env_line, '=') + 1);
}

bool	ms_is_same_envkey(char *dest, char *src)
{
	return (ft_strncmp(dest, src, ft_strlen(src)) == 0 \
			&& dest[ft_strlen(src)] == '=');
}

bool	ms_is_validenv(char *env_candidate)
{
	if (!(ft_isalpha(*env_candidate) || *env_candidate == '_'))
		return (false);
	env_candidate++;
	while (*env_candidate)
	{
		if (!ms_isenvchar(*env_candidate))
			return (false);
		env_candidate++;
	}
	return (true);
}

static char	*ms_getenv_line(char *env_key, t_data *data)
{
	t_list	*now;

	now = data->environ;
	while (now != NULL)
	{
		if (ms_is_same_envkey(now->content, env_key))
			return (now->content);
		now = now->next;
	}
	return (NULL);
}
