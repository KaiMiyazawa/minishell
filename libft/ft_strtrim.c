/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:16:44 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/11/18 15:56:53 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	check_set(char c, char const *set)
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

//int	main(void)
//{
//	char *s1 = "   xxx   xxx";
//	char *s2 = "";
//	char *ret = ft_strtrim(s1, " x");

//	if (!ft_strncmp(ret, s2, ft_strlen(s2) + 1))
//		printf("SUCSESS");
//	else
//		printf("FAILED");
//	if (ft_strlen(ret))
//		free(ret);
//}
