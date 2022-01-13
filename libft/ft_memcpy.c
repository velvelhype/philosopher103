/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 04:42:48 by kamori            #+#    #+#             */
/*   Updated: 2020/11/26 10:50:47 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*odest;

	odest = dst;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*((char *)dst++) = *((char *)src++);
	return (odest);
}
