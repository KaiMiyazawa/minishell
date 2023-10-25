/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:25:30 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/24 14:28:06 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_str(char *s1, char *s2)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (s1[count] != '\0')
		count++;
	while (s2[count2] != '\0')
		s1[count++] = s2[count2++];
	s1[count] = '\0';
}

void	print_error(char *error_msg, char *cause, bool exit_state, t_data *d)
{
	char	*error;
	int		size;

	size = 11 + ft_strlen(error_msg) + 1 + 1;
	if (cause != NULL)
		size += 2 + ft_strlen(cause);
	error = (char *)ft_calloc(sizeof(char), size);
	if (!error)
		perror(strerror(errno));
	ft_strlcpy(error, "minishell: ", 12);
	if (cause != NULL)
	{
		add_str(error, cause);
		add_str(error, ": ");
	}
	add_str(error, error_msg);
	add_str(error, "\n");
	if (write(2, error, size) == FAILED)
		perror(strerror(errno));
	free(error);
	g_state = exit_state;
}