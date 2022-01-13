/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_schr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:22:05 by kamori            #+#    #+#             */
/*   Updated: 2020/11/26 11:32:45 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	n;

	n = ft_strlen(s) - 1;
	if ((char)c == '\0')
		return ((char *)s + n + 1);
	while (s[n] && (n != -1))
	{
		if (s[n] == (char)c)
			return ((char *)&s[n]);
		n--;
	}
	return (NULL);
}
