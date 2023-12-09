/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:59:52 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/05 13:12:51 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fatal_error_exit(char *str)
{
	printf("Error: %s\n", str);
	exit(1);
}

static t_list	*ms_tlst_from_strlst(char *envp[], t_data *data)
{
	t_list	head;
	t_list	*cur;
	char	*content;
	size_t	i;

	head.next = NULL;
	cur = &head;
	i = 0;
	while (envp[i] != NULL)
	{
		content = ft_strdup_e(envp[i], data);
		if (content == NULL)
			exit(EXIT_FAILURE);
		cur->next = ft_lstnew_e(content, data);
		if (cur->next == NULL)
			exit(EXIT_FAILURE);
		cur = cur->next;
		i++;
	}
	return (head.next);
}

void	data_init(t_data *data, char **envp)
{
	data->envp = NULL;
	data->line_size = 0;
	data->line = NULL;
	data->path = make_path(getenv("PATH"));
	if (data->path == NULL)
		fatal_error_exit("PATH is not set");
	data->status = 0;
	data->tk = NULL;
	data->tk_size = 0;
	data->tk_head = NULL;
	data->tk_tail = NULL;
	data->pid = getpid();
	data->cmd = NULL;
	data->environ = ms_tlst_from_strlst(envp, data);
	g_sig_num = 0;
	g_cmd_ptr = data->cmd;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1] != NULL)
		fatal_error_exit("do not pass argments\n");
	data_init(&data, envp);
	if (DEBUG)
		confirm_data(&data);
	if (DEBUG)
		printf("%d\n", getpid());
	minishell(&data);
	free_all_data(&data, 1);
	return (data.status);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q minishell");
}
