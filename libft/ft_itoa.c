/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 03:10:19 by kamori            #+#    #+#             */
/*   Updated: 2020/11/28 23:16:03 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digitmaker(int n)
{
	int	digit;

	if (n == -2147483648)
		return (11);
	digit = 0;
	if (n < 0)
	{
		digit++;
		n = -n;
	}
	if (n == 0)
		digit++;
	while (n > 0)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

char	*ft_minkiller(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (12));
	if (!str)
		return (NULL);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		digit;
	int		end;
	char	*str;

	end = 0;
	if (n == -2147483648)
		return (ft_minkiller());
	digit = ft_digitmaker(n);
	str = (char *)malloc(sizeof(char) * (digit + 1));
	if (!str)
		return (NULL);
	str[digit] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		end++;
	}
	while (digit != end)
	{
		str[digit - 1] = n % 10 + '0';
		n = n / 10;
		digit--;
	}
	return (str);
}
