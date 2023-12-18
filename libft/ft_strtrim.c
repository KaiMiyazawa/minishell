/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:16:44 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/17 16:11:53 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//static int	check_set(char c, char const *set)
//{
//	while (*set)
//	{
//		if (*set == c)
//			return (1);
//		set++;
//	}
//	return (0);
//}

//char	*ft_strtrim(char const *s1, char const *set)
//{
//	size_t	count;
//	size_t	head;
//	size_t	tail;
//	char	*result;

//	if (!s1)
//		return (NULL);
//	head = 0;
//	while (s1[head] && check_set(s1[head], set))
//		head++;
//	tail = ft_strlen(s1);
//	while (head < tail && check_set(s1[tail - 1], set))
//		tail--;
//	result = (char *)malloc(sizeof(*s1) * (tail - head + 1));
//	if (!result)
//		return (NULL);
//	count = 0;
//	while (head < tail)
//		result[count++] = s1[head++];
//	result[count] = '\0';
//	return (result);
//}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		str = (char *)ft_calloc(sizeof(char), (j - i + 1));
		if (str)
			ft_strlcpy(str, &s1[i], j - i + 1);
	}
	return (str);
}
