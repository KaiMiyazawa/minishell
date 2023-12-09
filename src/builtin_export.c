/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:11:03 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:20:05 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		valid_check(char *argv);
static int		ms_set_environ(char **argv, t_data *data);
static t_list	*ms_lstnew_env(char *env_key);

int	ms_builtin_export(char *argv[], t_data *data)
{
	int		return_status;
	char	*eq;
	t_list	*now;

	if (argv[1] == NULL)
	{
		now = data->environ;
		while (now != NULL)
		{
			ft_putstr_fd(MSG_DECLARE, STDOUT_FILENO);
			eq = ft_strchr(now->content, '=');
			write(STDOUT_FILENO, now->content, eq - (char *)now->content + 1);
			ft_putstr_fd(STR_QUOTE, STDOUT_FILENO);
			ft_putstr_fd(eq + 1, STDOUT_FILENO);
			ft_putendl_fd(STR_QUOTE, STDOUT_FILENO);
			now = now->next;
		}
		return (0);
	}
	return_status = ms_set_environ(&argv[1], data);
	return (return_status);
}

void	ms_search_env_and_set(char *env_key, t_data *data)
{
	t_list	*now;
	t_list	*prev;
	t_list	*new;

	now = data->environ;
	prev = NULL;
	while (now != NULL)
	{
		if (ms_is_same_envkey(now->content, env_key))
		{
			free(now->content);
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

static void	valid_check(char *argv)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[i]) || (!ft_isalnum(argv[i]) && argv[i] != '_'))
		exit(EXIT_FAILURE);
	while (argv[i] != '\0')
	{
		if (argv[i] == '=')
			break ;
		if (argv[i] == '+' && argv[i + 1] == '=')
			break ;
		if (argv[i] == '-' && argv[i + 1] == '=')
			break ;
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
		{
			ft_putendl_fd(MSG_INVAL_ID, STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static int	ms_set_environ(char **argv, t_data *data)
{
	int		return_status;
	size_t	i;
	char	*eq;

	return_status = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		valid_check(argv[i]);
		eq = ft_strchr(argv[i], '=');
		if (eq == NULL && ++i)
			continue ;
		*eq = '\0';
		if (ms_is_validenv(argv[i]) == false)
		{
			*eq = '=';
			ft_putendl_fd(MSG_INVAL_ID, STDERR_FILENO);
			i++;
			return_status = 1;
		}
		else
			ms_search_env_and_set(argv[i++], data);
	}
	return (return_status);
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
