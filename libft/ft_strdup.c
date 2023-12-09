/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:35:52 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/11/18 15:55:35 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	size_t	count;
	char	*ptr;

	count = ft_strlen(str);
	if (str == NULL)
	{
		return (0);
	}
	ptr = (char *)malloc(sizeof(char) * (count + 1));
	count = 0;
	if (ptr != NULL)
	{
		while (str[count] != '\0')
		{
			ptr[count] = str[count];
			count++;
		}
		ptr[count] = '\0';
	}
	return (ptr);
}

/*
int	main(void)
{
	char	a[] = "asdfghjkl";
	char	*b;
	int		count;

	b = ft_strdup(a);
	printf("%s\n", b);
	count = 0;
	free(b);
}
*/
