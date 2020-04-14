/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:22:50 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/12 13:52:53 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*s;
	char	*d;
	size_t	n;
	size_t	len;

	d = dst;
	n = size;
	while (n-- && *d)
		++d;
	len = d - dst;
	n = size - len;
	if (!n--)
		return (len + ft_strlen(src));
	s = (char *)src;
	while (*s)
	{
		if (n)
		{
			*d++ = *s;
			--n;
		}
		++s;
	}
	*d = '\0';
	return (len + (s - src));
}
