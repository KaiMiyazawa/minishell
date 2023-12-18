/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:42:31 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/16 16:47:01 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//char	*ft_strchr(const char *s, int c)
//{
//	char	*result;

//	while (c >= 256)
//		c -= 256;
//	while (c < 0)
//		c += 256;
//	result = (char *)s;
//	while (*result != '\0')
//	{
//		if (*result == c)
//			return (result);
//		result++;
//	}
//	if (c == '\0')
//		return (result);
//	return (NULL);
//}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}
