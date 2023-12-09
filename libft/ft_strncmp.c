/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:30:24 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/11/27 21:44:50 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	count;

	count = 0;
	while (count < n && (s1[count] != '\0' || s2[count] != '\0'))
	{
		if (s1[count] != s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	count;

	count = 0;
	while (s1[count] != '\0' || s2[count] != '\0')
	{
		if (s1[count] != s2[count])
			return ((unsigned char)s1[count] - (unsigned char)s2[count]);
		count++;
	}
	return (0);
}

//int main(void){
//	char *a ="\200";
//	char *b ="\0";

//	printf("%d", ft_strncmp(a, b, 1));
//	printf("%d", strncmp(a, b, 1));
//}
