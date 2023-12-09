/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:37:35 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/29 23:19:07 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ms_clear_cmd_and_return_null(t_cmd *head)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = head;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->path != NULL)
			free(cur->path);
		cur->path = NULL;
		//if (cur->arg != NULL)
		//	free(cur->arg);
		cur->arg = NULL;
		if (cur->input != NULL)
		{
			//if (cur->input->path != NULL)
			free(cur->input->path);
			free(cur->input);
		}
		cur->input = NULL;
		if (cur->output != NULL)
		{
			if (cur->output->path != NULL)
				free(cur->output->path);
			free(cur->output);
		}
		cur->output = NULL;
		if (cur != NULL)
			free(cur);
		cur = NULL;
		cur = next;
	}
	return (NULL);
}

void	free_all_data(t_data *data, bool exit_flag)
{
	int	count;

	count = -1;
	if (exit_flag && data->path != NULL)
	{
		while (data->path[++count] != NULL)
			free(data->path[count]);
		if (data->path != NULL)
			free(data->path);
	}
	if (exit_flag && data->environ != NULL)
		ft_lstclear(&data->environ, free);
	if (data->line != NULL)
		free(data->line);
	data->line = NULL;
	data->line_size = 0;
	if (data->tk_head != NULL)
		tk_free_list(data);
	if (data->tk != NULL)
	{
		count = -1;
		while (data->tk[++count].word != NULL)
		{
			free(data->tk[count].word);
			data->tk[count].word = NULL;
		}
		free(data->tk);
		data->tk = NULL;
	}
	ms_clear_cmd_and_return_null(data->cmd);
	data->cmd = NULL;
	return ;
}

void	tk_free_list(t_data *data)
{
	t_tk_list	*tmp;
	t_tk_list	*tmp2;

	tmp = data->tk_head;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		if (tmp->word != NULL)
			free(tmp->word);
		tmp->word = NULL;
		if (tmp != NULL)
			free(tmp);
		tmp = NULL;
		tmp = tmp2;
	}
	data->tk_head = NULL;
	data->tk_tail = NULL;
	return ;
}

void	put_error_destroy_data_exit(t_data *data, char *error_msg, int state)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	free_all_data(data, 1);
	data->status = state;
	exit(state);
}

bool	put_error_destroy_data_continue(t_data *data,
	char *error_msg, int state)
{
	if (error_msg != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(error_msg, STDERR_FILENO);
	}
	free_all_data(data, 0);
	if (state != -1)
		data->status = state;
	return (false);
}

void	*ft_calloc_e(size_t n, size_t size, t_data *data)
{
	void	*p;

	p = ft_calloc(n, size);
	if (p == NULL)
		put_error_destroy_data_exit(data, "malloc error", 12);
	return (p);
}

char	*ft_strdup_e(char *s, t_data *data)
{
	char	*p;

	p = ft_strdup(s);
	if (p == NULL)
		put_error_destroy_data_exit(data, "malloc error", 12);
	return (p);
}

t_list	*ft_lstnew_e(void *content, t_data *data)
{
	t_list	*new;

	new = (t_list *)ft_calloc_e(sizeof(*new), 1, data);
	new->content = content;
	new->next = NULL;
	return (new);
}
