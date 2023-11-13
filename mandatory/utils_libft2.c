/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:58:27 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/07 11:55:39 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static bool	check_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	count;
	size_t	head;
	size_t	tail;
	char	*result;

	if (!s1)
		return (NULL);
	head = 0;
	while (s1[head] && check_set(s1[head], set))
		head++;
	tail = ft_strlen(s1);
	while (head < tail && check_set(s1[tail - 1], set))
		tail--;
	result = (char *)malloc(sizeof(*s1) * (tail - head + 1));
	if (!result)
		return (NULL);
	count = 0;
	while (head < tail)
		result[count++] = s1[head++];
	result[count] = '\0';
	return (result);
}
