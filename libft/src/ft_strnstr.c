/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:29:17 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/07 19:04:29 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	len1;
	size_t	len2;
	char	*s;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len)
		len1 = len;
	if (len2 > len1)
		return (NULL);
	s = (char*)s1;
	while ((size_t)(s - s1) <= len1 - len2)
	{
		if (!ft_strncmp(s, s2, len2))
			return (s);
		++s;
	}
	return (NULL);
}
