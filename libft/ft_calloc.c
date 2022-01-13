/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 03:05:00 by kamori            #+#    #+#             */
/*   Updated: 2020/11/26 11:17:57 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*a;

	a = malloc(nmemb * size);
	if (!a)
		return (NULL);
	else
		ft_bzero(a, nmemb * size);
	return ((void *)a);
}
