/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 06:25:39 by kamori            #+#    #+#             */
/*   Updated: 2020/11/28 18:00:54 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	elen;
	size_t	ori;

	elen = 0;
	while (dst[elen] && elen < dstsize)
		elen++;
	ori = elen;
	while (src[elen - ori] && elen + 1 < dstsize)
	{
		dst[elen] = src[elen - ori];
		elen++;
	}
	if (ori < dstsize)
		dst[elen] = '\0';
	return (ori + ft_strlen(src));
}
