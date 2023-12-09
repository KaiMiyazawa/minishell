/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:43:55 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/05/21 10:54:25 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t size)
{
	unsigned char	*p;
	size_t			count;

	count = 0;
	p = (unsigned char *)s;
	while (count < size)
	{
		*p++ = (unsigned char)c;
		count++;
	}
	return (s);
}

/*
main(void)
{
	char a[] = "abc";

	printf("%s\n", ft_memset(a,'x', 5));
	printf("%s\n", memset(a,'x', 5));
}
*/
