/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:53:40 by kamori            #+#    #+#             */
/*   Updated: 2020/11/25 00:16:15 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	s;
	size_t	f;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	s = 0;
	while (haystack[s] != '\0' && s < len)
	{
		f = 0;
		while (needle[f] == haystack[s + f] && haystack[s + f] && len > (s + f))
		{
			f++;
			if (needle[f] == '\0')
				return ((char *)&haystack[s]);
		}
		s++;
	}
	return (NULL);
}
