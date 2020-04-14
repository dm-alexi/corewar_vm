/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:32:57 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/10 19:33:46 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
** The function swaps two regions of memory.
** Undefined behavior in case of overlapping.
*/

void	ft_memswap(void *a, void *b, size_t size)
{
	unsigned char	*s;
	unsigned char	*t;
	size_t			i;

	if (a == b || !size)
		return ;
	s = a;
	t = b;
	i = 0;
	while (i < size)
	{
		*(s + i) ^= *(t + i);
		*(t + i) ^= *(s + i);
		*(s + i) ^= *(t + i);
		++i;
	}
}
