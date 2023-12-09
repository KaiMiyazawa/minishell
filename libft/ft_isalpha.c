/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:27:56 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/05/21 10:53:47 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int character)
{
	if ((character >= 'A' && character <= 'Z' )
		|| (character >= 'a' && character <= 'z'))
		return (1);
	else
		return (0);
}

/*
#include<stdio.h>

int main(void)
{
	char a[] = "";

	printf("%d\n", ft_isdigit(a));
}
*/