/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fdnorm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 01:39:18 by kamori            #+#    #+#             */
/*   Updated: 2020/11/28 02:11:49 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nc;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nc = (unsigned int)(n * -1);
	}
	else
		nc = (unsigned int)n;
	if (nc >= 10)
		ft_putnbr_fd(nc / 10, fd);
	ft_putchar_fd((char)(nc % 10 + 48), fd);
}
