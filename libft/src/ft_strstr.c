/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:09:58 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/05 22:07:54 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*s;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
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
