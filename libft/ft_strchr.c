/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_schr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:22:05 by kamori            #+#    #+#             */
/*   Updated: 2020/11/26 11:32:32 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	n;

	n = 0;
	if (c == '\0')
	{
		while (s[n] != '\0')
			n++;
		return ((char *)&s[n]);
	}
	while (s[n] && (s != NULL))
	{
		if (s[n] == (char)c)
			return ((char *)&s[n]);
		n++;
	}
	return (NULL);
}
