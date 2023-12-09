/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:52:15 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/05/24 14:35:33 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	unsigned int	count;
	unsigned char	*s1_char;
	unsigned char	*s2_char;

	s1_char = (unsigned char *)s1;
	s2_char = (unsigned char *)s2;
	count = 0;
	while (count < size)
	{
		if (s1_char[count] != s2_char[count])
			return (s1_char[count] - s2_char[count]);
		count++;
	}
	return (0);
}

//int main(void){
//	char a[] ="aiueo";
//	char b[] ="aiukeo";

//	printf("%d", ft_memcmp(a, b, 4));

//}
