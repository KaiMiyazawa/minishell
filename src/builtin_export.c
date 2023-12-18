/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:11:03 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/13 16:42:44 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		valid_check(char *argv);
static int		ms_set_environ(char **argv, t_data *data);
static void		search_env_and_set_ex(char *env_key, t_data *data, t_list *now);

int	ms_builtin_export(char *argv[], t_data *data)
{
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
	return (ms_set_environ(&argv[1], data));
}

static bool	is_some_envkey_full(char *dest, char *src)
{
	int	i;

	i = 0;
	while (dest[i] == src[i] && (dest[i] != '\0' && src[i] != '\0'))
	{
		if (dest[i] == '=')
		{
			if (src[i] == '=')
				return (true);
			else
				return (false);
		}
		i++;
	}
	return (false);
}

static void	search_env_and_set_ex(char *env_key, t_data *data, t_list *now)
{
	t_list	*prev;
	t_list	*new;

	prev = NULL;
	while (now != NULL)
	{
		if (is_some_envkey_full(now->content, env_key))
		{
			free(now->content);
			now->content = NULL;
			now->content = ft_strdup(env_key);
			if (now->content == NULL)
				exit(EXIT_FAILURE);
			return ;
		}
		prev = now;
		now = now->next;
	}
	new = lstnew_env_ex(env_key);
	if (prev == NULL)
		data->environ = new;
	else
		prev->next = new;
}

static int	valid_check(char *argv)
{
	int		i;

	i = 0;
	if (ft_isdigit(argv[i]) || (!ft_isalpha(argv[i]) && argv[i] != '_'))
		return (1);
	i++;
	while (argv[i] != '\0')
	{
		if (argv[i] == '=')
			return (0);
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
			return (1);
		i++;
	}
	return (-1);
}

static int	ms_set_environ(char **argv, t_data *data)
{
	int		return_status;
	size_t	i;
	int		check;

	return_status = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		check = valid_check(argv[i]);
		if (check != 0)
		{
			if (check == 1)
				ft_putendl_fd(MSG_INVAL_ID, STDERR_FILENO);
			if (check == 1)
				return_status = 1;
			i++;
			continue ;
		}
		search_env_and_set_ex(argv[i], data, data->environ);
		i++;
	}
	return (return_status);
}
