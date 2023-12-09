/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:22:29 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/06/21 18:04:55 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	del_speace(char *str)
{
	int	count;

	count = 0;
	while (str[count] == ' ' || (str[count] >= 9 && str[count] <= 13))
		count++;
	return (count);
}

static int	del_sign(int count, char *str)
{
	if (str[count] == '-' || str[count] == '+')
		return (1);
	return (0);
}

static int	minus_judge(int count, char *str)
{
	if (str[count] == '-')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		count;
	int		minus_flag;

	num = 0;
	count = del_speace((char *)str);
	minus_flag = minus_judge(count, (char *)str);
	count += del_sign(count, (char *)str);
	while (str[count] >= '0' && str[count] <= '9')
	{
		if (minus_flag == 0 && num > (LONG_MAX - str[count] + '0') / 10)
			return ((int)LONG_MAX);
		if (minus_flag == 1 && num > (LONG_MAX - str[count] + '0') / 10
			&& - num * 10 + str[count] - '0' != LONG_MIN)
			return ((int)LONG_MIN);
		num *= 10;
		num += str[count] - '0';
		count++;
	}
	if (minus_flag == 1)
		num *= -1;
	return (num);
}

//#include<stdio.h>
//int main(void)
//{
//	char a[] = "0";
//	char b[] = "  	-1234ab567";
//	char c[] = "  	   	---+--+  1234ab567";
//	printf("%d\n", ft_atoi(a));
//	printf("%d\n", ft_atoi(b));
//	printf("%d\n", ft_atoi(c));
//	printf("%d\n", atoi(a));
//	printf("%d\n", atoi(b));
//	printf("%d\n", atoi(c));
//}
