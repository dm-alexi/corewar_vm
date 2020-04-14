/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:24:46 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/07 11:40:04 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	const unsigned char		*s;
	unsigned char			*t;

	if (dst == src)
		return (dst);
	t = dst;
	s = src;
	if (s > t)
		while (num--)
			*t++ = *s++;
	else
	{
		s += num - 1;
		t += num - 1;
		while (num--)
			*t-- = *s--;
	}
	return (dst);
}
