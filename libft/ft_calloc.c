/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:42:59 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/17 15:48:07 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void	*ft_calloc(size_t n, size_t size)
//{
//	void	*result;

//	if (size != 0 && n > SIZE_MAX / size)
//		return (NULL);
//	result = (void *)malloc(n * size);
//	if (!result)
//		ft_bzero(result, n * size);
//	return (result);
//}

void	*ft_calloc(size_t n, size_t size)
{
	size_t	b;
	void	*p;

	if (n == 0 || size == 0)
	{
		n = 1;
		size = 1;
	}
	b = n * size;
	p = malloc(b);
	if (p == NULL)
		return (NULL);
	else
		ft_bzero(p, b);
	return (p);
}
