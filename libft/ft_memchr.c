/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:35:32 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/05/21 10:54:08 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*tmp;

	tmp = (char *)s;
	while (n > 0)
	{
		if (*tmp == (char)c)
			return (tmp);
		tmp++;
		n--;
	}
	return (NULL);
}

//int	main(void)
//{
//	char a[20] = "aiouieo";
//	printf("%s\n",ft_memchr(a,'o',sizeof(a)));
//	printf("%s\n",memchr(a,'o',sizeof(a)));
//}