/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:06:39 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/05/31 20:21:09 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dest && !size)
		return (src_len);
	dest_len = ft_strlen(dest);
	i = 0;
	if (dest_len < size -1 && size > 0)
	{
		while (i < size - dest_len - 1 && src[i])
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		dest[i + dest_len] = '\0';
	}
	if (size <= dest_len)
		return (size + src_len);
	return (src_len + dest_len);
}

//int main(void)
//{
//	int	num = 0;
//	char a[20] = "aiueo";
//	char b[] = "1234";
//	printf("%lu\n", strlcat(a, b, num));
//	char c[20] = "aiueo";
//	printf("%zu\n", ft_strlcat(c, b, num));

//	//char *src1 = malloc(100 * sizeof(char));
//	//char *src2 = malloc(100 * sizeof(char));

//	//for (int i = 0; i < 99; i++)
//	//{
//	//	src1[i] = i + 1;
//	//	src2[i] = i + 1;
//	//}
//	//printf("%lu\n", ft_strlcat(NULL, src1, 0));
//	//printf("%lu\n", strlcat(NULL, src2, 0));

//}
