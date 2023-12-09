/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:34:19 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/05/31 13:33:22 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			count;
	unsigned char	*dest_char;
	unsigned char	*src_char;

	dest_char = (unsigned char *)dest;
	src_char = (unsigned char *)src;
	count = 0;
	if (!dest && !src)
		return (NULL);
	while (count < n)
	{
		dest_char[count] = src_char[count];
		count++;
	}
	return (dest);
}

//int	main(void)
//{
//	char s1[] ="abcdefg";
//	char s2[] ="xzy";

//	printf("%s\n",memcpy(s1,s2,3));
//	printf("%s\n",ft_memcpy(s1,s2,3));
//}