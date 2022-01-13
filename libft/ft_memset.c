/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memsetnorm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 01:36:49 by kamori            #+#    #+#             */
/*   Updated: 2021/12/23 23:48:01 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*censored;

	censored = (unsigned char *)b;
	while (len > 0)
	{
		*censored = (unsigned char)c;
		censored++;
		len--;
	}
	return (b);
}
