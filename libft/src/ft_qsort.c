/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 22:51:36 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/10 19:44:39 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*partition(void *low, void *high, size_t size,
	int (*compar)(const void*, const void*))
{
	unsigned char	*l;
	unsigned char	*r;
	unsigned char	*p;

	p = (unsigned char *)low;
	r = (unsigned char *)high;
	l = p + size;
	ft_memswap(p, p + (r - p) / size / 2 * size, size);
	while (1)
	{
		while (l < r && compar(l, p) < 0)
			l += size;
		while (compar(r, p) > 0)
			r -= size;
		if (l >= r)
		{
			ft_memswap(p, r, size);
			return ((void*)r);
		}
		ft_memswap(l, r, size);
		l += size;
		r -= size;
	}
}

void			ft_qsort(void *base, size_t num, size_t size,
	int (*compar)(const void*, const void*))
{
	unsigned char	*l;
	unsigned char	*r;
	unsigned char	*p;

	if (!base || num < 2 || !size || !compar)
		return ;
	if (num < 10)
	{
		ft_isort(base, num, size, compar);
		return ;
	}
	l = (unsigned char*)base;
	r = l + size * (num - 1);
	p = (unsigned char*)partition(base, r, size, compar);
	ft_qsort(base, (p - l) / size, size, compar);
	ft_qsort(p + size, (r - p) / size, size, compar);
}
