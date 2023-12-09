/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:24:34 by hrinka            #+#    #+#             */
/*   Updated: 2023/12/09 11:45:41 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_and_return(void *malloc_obj)
{
	free(malloc_obj);
	return (NULL);
}

void	*print_err_set_status_return_null(char *str, int status)
{
	if (str != NULL)
		ft_putendl_fd(str, STDERR_FILENO);
	if (status >= 0)
		g_shell.status = status;
	return (NULL);
}

void	ms_init_fd(int fd[2])
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
}

bool	ms_is_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) != 0)
		return (false);
	if (S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}

char	*ft_strtrim_space(char const *s1)
{
	size_t	count;
	size_t	head;
	size_t	tail;
	char	*result;

	if (!s1)
		return (NULL);
	head = 0;
	while (s1[head] && (s1[head] == ' ' || s1[head] == '\t'))
		head++;
	tail = ft_strlen(s1);
	while (head < tail && (s1[head] == ' ' || s1[head] == '\t'))
		tail--;
	result = (char *)ft_calloc(sizeof(*s1), (tail - head + 1));
	if (!result)
		return (NULL);
	count = 0;
	while (head < tail)
		result[count++] = s1[head++];
	result[count] = '\0';
	return (result);
}
