/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:17:32 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/05/21 16:38:44 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int character)
{
	if (ft_isalpha(character) || ft_isdigit(character))
		return (1);
	else
		return (0);
}

//#include <stdio.h>
//#include <ctype.h>
//#include <limits.h>

//int main(void)
//{
//	for (int i = -5; i < UCHAR_MAX +5; ++i) {
//		if (isalnum(i)) {
//			printf("%c (%x)\n", i, i);
//		}
//	}
//}