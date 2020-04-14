/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:33:55 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/10 19:45:20 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insertion sort. Stable.
*/

void	ft_isort(void *base, size_t num, size_t size,
	int (*compar)(const void*, const void*))
{
	unsigned char	*b;
	unsigned char	*s;
	unsigned char	*t;

	if (!base || num < 2 || !size || !compar)
		return ;
	b = (unsigned char*)base;
	s = b;
	while ((s - b) / size < num)
	{
		t = s;
		while (t > b && compar(t - size, t) > 0)
		{
			ft_memswap(t, t - size, size);
			t -= size;
		}
		s += size;
	}
}
