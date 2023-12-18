/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:06:39 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/16 16:29:22 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//size_t	ft_strlcat(char *dest, const char *src, size_t size)
//{
//	size_t	i;
//	size_t	dest_len;
//	size_t	src_len;

//	src_len = ft_strlen(src);
//	if (!dest && !size)
//		return (src_len);
//	dest_len = ft_strlen(dest);
//	i = 0;
//	if (dest_len < size -1 && size > 0)
//	{
//		while (i < size - dest_len - 1 && src[i])
//		{
//			dest[dest_len + i] = src[i];
//			i++;
//		}
//		dest[i + dest_len] = '\0';
//	}
//	if (size <= dest_len)
//		return (size + src_len);
//	return (src_len + dest_len);
//}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
