/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:42:31 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/11/18 15:55:00 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*result;

	while (c >= 256)
		c -= 256;
	while (c < 0)
		c += 256;
	result = (char *)s;
	while (*result != '\0')
	{
		if (*result == c)
			return (result);
		result++;
	}
	if (c == '\0')
		return (result);
	return (NULL);
}

//int	main(void)
//{
//	char a[20] = "aiueo";
//	char *s = "libft-test-tokyo";
//	printf("%s\n",ft_strchr(s,'i' - 256));
//	printf("%s\n",strchr(s,'i' - 256));
//}
