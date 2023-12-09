/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:01:54 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/11/24 18:48:35 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		count;
	char				*result;

	if (!s)
		return (NULL);
	result = (char *)malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	count = 0;
	while (s[count] != '\0')
	{
		result[count] = f(count, s[count]);
		count++;
	}
	result[count] = '\0';
	return (result);
}

//char	ppp(unsigned int a, char b)
//{
//	return (b + a);
//}

//int	main(void)
//{
//	char s[] = "asdfghjkl";
//	printf("%s\n",ft_strmapi(s, ppp));
//}
