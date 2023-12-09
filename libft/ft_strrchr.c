/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:08:58 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/05/31 20:08:33 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		count ;
	char	*result;

	while (c >= 256)
		c -= 256;
	while (c < 0)
		c += 256;
	count = ft_strlen(s);
	s += count;
	while (count >= 0)
	{
		if (*s == c)
		{
			result = (char *)s;
			return (result);
		}
		s--;
		count--;
	}
	return (NULL);
}

//int	main(void)
//{
//	char a[20] = "aiouieo";
//	printf("%s\n",ft_strrchr(a,'\0'));
//	printf("%s\n",strrchr(a,'\0'));
//}
