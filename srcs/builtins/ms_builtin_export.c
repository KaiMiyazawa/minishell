/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:11:03 by hrinka            #+#    #+#             */
/*   Updated: 2023/11/27 22:08:17 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				ms_builtin_export(char *argv[], t_data *data);
static int		ms_print_env_with_declare(t_data *data);
static int		ms_set_environ(char **argv, t_data *data);
void			ms_search_env_and_set(char *env_key, t_data *data);
static t_list	*ms_lstnew_env(char *env_key, t_data *data);

int	ms_builtin_export(char *argv[], t_data *data)
{
	int	return_status;

	if (argv[1] == NULL)
		return (ms_print_env_with_declare(data));
	return_status = ms_set_environ(&argv[1], data);
	return (return_status);
}

static int	ms_print_env_with_declare(t_data *data)
{
	t_list	*cur;
	char	*eq;

	cur = data->environ;
	while (cur != NULL)
	{
		ft_putstr_fd(MSG_DECLARE, STDOUT_FILENO);
		eq = ft_strchr(cur->content, '=');
		write(STDOUT_FILENO, cur->content, eq - (char *)cur->content + 1);
		ft_putstr_fd(STR_QUOTE, STDOUT_FILENO);
		ft_putstr_fd(eq + 1, STDOUT_FILENO);
		ft_putendl_fd(STR_QUOTE, STDOUT_FILENO);
		cur = cur->next;
	}
	return (0);
}

bool	ms_isenvchar(int c)
{
	return (ft_isalnum(c) || c == '_');
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

int	ms_set_environ(char **argv, t_data *data)
{
	int		return_status;
	size_t	i;
	char	*eq;

	return_status = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		eq = ft_strchr(argv[i], '=');
		if (eq == NULL)
		{
			i++;
			continue ;
		}
		*eq = '\0';
		if (ms_is_validenv(argv[i]) == false)
		{
			*eq = '=';
			printf(MSG_INVAL_ID, "export", argv[i++]);
			return_status = 1;
		}
		else
			ms_search_env_and_set(argv[i++], data);
	}
	return (return_status);
}

void	ms_search_env_and_set(char *env_key, t_data *data)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*new;

	cur = data->environ;
	prev = NULL;
	while (cur != NULL)
	{
		if (ms_is_same_envkey(cur->content, env_key))
		{
			free(cur->content);
			env_key[ft_strlen(env_key)] = '=';
			cur->content = ft_strdup(env_key);
			if (cur->content == NULL)
				put_error_destroy_data_exit(data, "malloc error", 12);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	new = ms_lstnew_env(env_key, data);
	if (prev == NULL)
		data->environ = new;
	else
		prev->next = new;
}

t_list	*ms_lstnew_env(char *env_key, t_data *data)
{
	t_list	*new;
	char	*str;

	env_key[ft_strlen(env_key)] = '=';
	str = ft_strdup(env_key);
	if (str == NULL)
		put_error_destroy_data_exit(data, "malloc error", 12);
	new = ft_lstnew_e(str, data);
	if (new == NULL || new->content == NULL)
		exit(EXIT_FAILURE);
	return (new);
}
