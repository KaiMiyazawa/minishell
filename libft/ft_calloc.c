/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:42:59 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/12/02 22:51:52 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*result;

	if (size != 0 && n > SIZE_MAX / size)
		return (NULL);
	result = (void *)malloc(n * size);
	if (!result)
		ft_bzero(result, n * size);
	return (result);
}

//int main(void)
//{
//	int* values = ft_calloc(ALLOCATE_SIZE, sizeof(int));
//	if (values == NULL) {
//		exit(EXIT_FAILURE);
//	}

//	for (int i = 0; i < ALLOCATE_SIZE; ++i) {
//		printf("%d ", values[i]);
//	}
//	printf("\n");

//	for (int i = 0; i < ALLOCATE_SIZE; ++i) {
//		values[i] = i;
//	}

//	for (int i = 0; i < ALLOCATE_SIZE; ++i) {
//		printf("%d ", values[i]);
//	}
//	printf("\n");

//	free(values);
//}
