/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:58:24 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/09 21:46:57 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strncat(char *dst, const char *src, size_t num)
{
	char	*s;

	if (!num)
		return (dst);
	s = dst;
	while (*s)
		++s;
	while (num && *src)
	{
		--num;
		*s++ = *src++;
	}
	*s = '\0';
	return (dst);
}
