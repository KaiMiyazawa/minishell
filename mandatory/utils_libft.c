/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:59:04 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/10/18 16:04:31 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*result;
	size_t	count;

	if (size != 0 && n > SIZE_MAX / size)
		return (NULL);
	result = (void *)malloc(n * size);
	if (!result)
		return (NULL);
	count = 0;
	while (count < n * size)
	{
		*(char *)(result + count) = 0;
		count++;
	}
	return (result);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size > 0)
	{
		while (count < size - 1 && src[count])
		{
			dest[count] = src[count];
			count++;
		}
		dest[count] = '\0';
	}
	while (src[count])
		count++;
	return (count);
}
