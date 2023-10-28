/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:08:46 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/10/18 17:20:38 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	g_state;

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

void	print_error(char *error_msg, char *addition, bool exit_state, t_data *d)
{
	char	*error;
	int		size;

	size = 11 + ft_strlen(error_msg) + 1 + 1;
	if (addition != NULL)
		size += 2 + ft_strlen(addition);
	error = (char *)ft_calloc(sizeof(char), size);
	if (!error)
		perror(strerror(errno));
	ft_strlcpy(error, "minishell: ", 12);
	if (addition != NULL)
	{
		add_str(error, addition);
		add_str(error, ": ");
	}
	add_str(error, error_msg);
	add_str(error, "\n");
	if (write(2, error, size) == FAILED)
		perror(strerror(errno));
	free(error);
	g_state = exit_state;
}

void	data_init(int ac, char **av, char **ev, t_data *data)
{
	g_state = 0;
	data->ac = ac;
	data->av = av;
	data->envp = ev;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data_init(argc, argv, envp, &data);
	minishell(&data);
	exit (0);
}

//__attribute__((destructor))
//static void destructor() {
//	system("leaks -q a.out");
//}
