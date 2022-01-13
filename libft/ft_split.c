/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamori <kamori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 07:30:07 by kamori            #+#    #+#             */
/*   Updated: 2020/11/29 07:33:14 by kamori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	flvlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s == c)
		{
			while (*s == c)
				s++;
		}
		if (*s)
			len++;
		if (*s && *s != c)
		{
			while (*s && *s != c)
				s++;
		}
	}
	return (len);
}

int	sizeslv(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**free_lvs(char **lvs, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(lvs[i]);
		i++;
	}
	free(lvs);
	return (NULL);
}

char	**slvfiller(char const *s, char **lvs, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			lvs[j] = (char *)malloc(sizeof(char) * (sizeslv(s, c) + 1));
			if (!(lvs[j]))
				return (free_lvs(lvs, j));
			ft_strlcpy(lvs[j], s, (sizeslv(s, c) + 1));
			i++;
			j++;
		}
		while (*s && *s != c)
			s++;
	}
	lvs[j] = NULL;
	return (lvs);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		len;

	if (s == NULL)
		return (NULL);
	len = flvlen(s, c);
	dst = (char **)malloc(sizeof(char *) * len + 1);
	if (!dst)
		return (NULL);
	return (slvfiller(s, dst, c));
}
