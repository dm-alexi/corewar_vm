/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 22:16:14 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/07 11:39:07 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int val, size_t num)
{
	const unsigned char		*s;
	unsigned char			*t;
	unsigned char			c;

	t = dst;
	s = src;
	c = (unsigned char)val;
	while (num && (*t++ = *s++) != c)
		--num;
	return (num ? (void*)t : NULL);
}
