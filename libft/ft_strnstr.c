/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:03:25 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/05/31 14:36:21 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		count1;
	int		count2;
	char	*result;

	count1 = -1;
	if (!big && !len)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[++count1] != '\0' && len > 0)
	{
		count2 = 0;
		while (big[count1 + count2] != '\0'
			&& big[count1 + count2] == little[count2])
			count2++;
		if ((size_t)count2 > len--)
			break ;
		if (little[count2] == '\0')
		{
			result = (char *)big;
			return (result + count1);
		}
	}
	return (NULL);
}

//int	main(void)
//{
//	char	*p;
//	size_t num = 3;
//	//sizeof("abcdfghijk");

//	p = ft_strnstr("abcdefghijk", "bc", num);
//	printf("検索文字列が見つかった場所から表示→ %s\n",p);
//	p = strnstr("abcdefghijk", "bc", num);
//	printf("検索文字列が見つかった場所から表示→ %s\n",p);
//	return (0);
//}
