/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:11:31 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/05/25 15:20:37 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t size)
{
	int	count;

	if (!s1 && !s2)
		return (NULL);
	if (s1 > s2)
	{
		count = (int)size - 1;
		while (count >= 0)
		{
			*(char *)(s1 + count) = *(char *)(s2 + count);
			count--;
		}
	}
	else
	{
		count = 0;
		while (count < (int)size)
		{
			*(char *)(s1 + count) = *(char *)(s2 + count);
			count++;
		}
	}
	return (s1);
}

//int	main(void)
//{
//	char s1[] ="abcdefg";
//	char s2[] ="xzy";

//	printf("%s\n",memmove(s1,s2,3));
//	printf("%s\n",ft_memmove(s1,s2,3));
//}
