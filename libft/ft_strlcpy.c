/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:10:05 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/16 16:48:02 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//size_t	ft_strlcpy(char *dest, const char *src, size_t size)
//{
//	size_t	count;

//	count = 0;
//	if (size > 0)
//	{
//		while (count < size - 1 && src[count])
//		{
//			dest[count] = src[count];
//			count++;
//		}
//		dest[count] = '\0';
//	}
//	while (src[count])
//		count++;
//	return (count);
//}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
