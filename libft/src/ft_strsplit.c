/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:10:41 by sscarecr          #+#    #+#             */
/*   Updated: 2020/02/02 11:55:17 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_word_count(char const *s, char c)
{
	size_t	n;

	if (!s)
		return (0);
	n = 0;
	while (*s == c)
		++s;
	while (*s)
	{
		while (*s && *s != c)
			++s;
		++n;
		while (*s == c)
			++s;
	}
	return (n);
}

static char		**clean(char **arr, size_t n)
{
	while (n--)
		free(arr[n]);
	free(arr);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	const char	*t;
	char		**arr;
	size_t		n;
	size_t		i;

	n = ft_word_count(s, c);
	if (!s || !(arr = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	i = 0;
	while (*s == c)
		++s;
	while (i < n)
	{
		t = s;
		while (*s && *s != c)
			++s;
		if (!(arr[i] = (char*)malloc(s - t + 1)))
			return (clean(arr, i));
		ft_strncpy(arr[i], t, s - t);
		arr[i++][s - t] = '\0';
		while (*s == c)
			++s;
	}
	arr[i] = NULL;
	return (arr);
}
