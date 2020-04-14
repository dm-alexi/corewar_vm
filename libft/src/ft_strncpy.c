/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 22:00:14 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/09 21:16:35 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strncpy(char *dst, const char *src, size_t num)
{
	char	*s;

	s = dst;
	while (num && *src)
	{
		--num;
		*s++ = *src++;
	}
	while (num--)
		*s++ = '\0';
	return (dst);
}
