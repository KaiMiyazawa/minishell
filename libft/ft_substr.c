/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:38:31 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/05/31 14:49:53 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cal_size(size_t len, char const *s)
{
	size_t	size;

	size = ft_strlen(s);
	if (size < len + 1)
		return (size);
	else
		return (len + 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	count;
	size_t	size;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
	{
		result = (char *)ft_calloc(1, 1);
		return (result);
	}
	size = cal_size(len, s);
	result = (char *)malloc((size) * sizeof(char));
	if (!result)
		return (NULL);
	count = 0;
	while (count < len && s[start + count] != '\0')
	{
		result[count] = s[start + count];
		count++;
	}
	result[count] = '\0';
	return (result);
}

//int	main(void)
//{
//	printf("%s\n", ft_substr("asdfghjkl", 3, 5));
//}
