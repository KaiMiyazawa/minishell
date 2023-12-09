/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmiyazaw <kmiyazaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:23:41 by kmiyazaw          #+#    #+#             */
/*   Updated: 2023/05/28 19:28:40 by kmiyazaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	n_long;

	n_long = (long)n;
	if (n_long < 0)
	{
		n_long *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n_long > 9)
		ft_putnbr_fd((int)(n_long / 10), fd);
	c = (n_long % 10) + '0';
	write(fd, &c, 1);
}

//int main(void)
//{
//	ft_putnbr_fd(INT_MAX -1, 1);
//}
