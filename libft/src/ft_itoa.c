/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:18:19 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/19 11:34:48 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int		len;

	len = (n < 0);
	while (n && ++len)
		n /= 10;
	return (len);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		len;

	if (!(len = intlen(n)))
		return (ft_strdup("0"));
	if (!(s = (char*)malloc(len + 1)))
		return (NULL);
	s[len] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		s[--len] = -(n % 10) + '0';
		n = -(n / 10);
	}
	while (n)
	{
		s[--len] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}
