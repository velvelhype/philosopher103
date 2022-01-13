/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 00:17:48 by kamori            #+#    #+#             */
/*   Updated: 2020/11/28 17:06:29 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cpy_proc(int j, char const *s, char *cpy)
{
	int	i;

	i = 0;
	while (s[i])
	{
		cpy[j++] = s[i];
		i++;
	}
	return (j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	one;
	size_t	two;
	size_t	j;
	char	*cpy;

	one = ft_strlen(s1);
	two = ft_strlen(s2);
	cpy = (char *)malloc(sizeof(char) * (one + two + 1));
	if (!cpy)
		return (NULL);
	j = 0;
	j = cpy_proc(j, s1, cpy);
	j = cpy_proc(j, s2, cpy);
	cpy[j] = '\0';
	return (cpy);
}
