/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:52:16 by kamori            #+#    #+#             */
/*   Updated: 2020/11/25 00:48:41 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	fc;
	int				i;

	i = 0;
	fc = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (str[i] == fc)
			return (str + i);
		i++;
	}
	return (NULL);
}
