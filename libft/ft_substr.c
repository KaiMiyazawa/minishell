/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:38:31 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/16 16:29:31 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//static size_t	cal_size(size_t len, char const *s)
//{
//	size_t	size;

//	size = ft_strlen(s);
//	if (size < len + 1)
//		return (size);
//	else
//		return (len + 1);
//}

//char	*ft_substr(char const *s, unsigned int start, size_t len)
//{
//	char	*result;
//	size_t	count;
//	size_t	size;

//	if (!s)
//		return (NULL);
//	if (start > (unsigned int)ft_strlen(s))
//	{
//		result = (char *)ft_calloc(1, 1);
//		return (result);
//	}
//	size = cal_size(len, s);
//	result = (char *)malloc((size) * sizeof(char));
//	if (!result)
//		return (NULL);
//	count = 0;
//	while (count < len && s[start + count] != '\0')
//	{
//		result[count] = s[start + count];
//		count++;
//	}
//	result[count] = '\0';
//	return (result);
//}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)ft_calloc(sizeof(*s), (len + 1));
	if (str == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}
