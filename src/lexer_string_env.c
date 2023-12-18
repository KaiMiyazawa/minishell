/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:15:45 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/13 17:10:28 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ms_expand_special_env(char *line, size_t *pos, t_data *data);

t_list	*ms_expand_envvar_dquote(char *line, size_t len, t_data *data)
{
	size_t	pos;
	char	*dollar;
	t_list	*head;

	head = NULL;
	pos = 0;
	while (pos < len)
	{
		dollar = ft_strchr(&line[pos], CHRS_QUOTE[0]);
		errno = 0;
		if (dollar == &line[pos])
			ft_lstadd_back(&head, ms_expand_envvar(line, &pos, \
					len - pos, data));
		else
		{
			if (dollar == NULL || dollar >= line + len)
				dollar = line + len;
			ms_lexer_string_lstadd_back_substr(&head, line, \
				pos, dollar - &line[pos]);
			pos = dollar - line;
		}
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	return (head);
}

t_list	*ms_expand_envvar(char *line, size_t *pos, size_t len, t_data *data)
{
	size_t	i;
	char	*env_key;
	char	*env_value;

	*pos += 1;
	i = 0;
	if (line[*pos] == '?' || ft_isdigit(line[*pos]) || line[*pos] == '$')
		return (ms_expand_special_env(line, pos, data));
	while (i + 1 < len && line[*pos + i] && ms_isenvchar(line[*pos + i]))
		i++;
	if (i == 0)
		return (ft_lstnew(ft_strdup(STR_EXPAND)));
	env_key = ft_substr(line, *pos, i);
	*pos += i;
	if (env_key == NULL)
		exit(EXIT_FAILURE);
	env_value = ms_getenv_val(env_key, data);
	free(env_key);
	env_key = NULL;
	if (env_value == NULL)
		return (NULL);
	return (ft_lstnew(ft_strdup(env_value)));
}

bool	ms_isenvchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static t_list	*ms_expand_special_env(char *line, size_t *pos, t_data *data)
{
	char	*dollar;

	if (line[*pos] == '?')
	{
		*pos += 1;
		return (ft_lstnew(ft_itoa(data->status)));
	}
	else if (line[*pos] == '$')
	{
		dollar = ft_calloc(2, sizeof(char));
		dollar[0] = '$';
		dollar[1] = '\0';
		*pos += 1;
		return (ft_lstnew(dollar));
	}
	else if (ft_isdigit(line[*pos]))
	{
		*pos += 1;
		return (ft_lstnew(ft_strdup(STR_EMPTY)));
	}
	return (NULL);
}
