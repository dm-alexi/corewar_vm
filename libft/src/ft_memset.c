/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:25:56 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/07 11:38:35 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t num)
{
	unsigned char	c;
	unsigned char	*s;

	c = (unsigned char)val;
	s = ptr;
	while (num--)
		*s++ = c;
	return (ptr);
}
