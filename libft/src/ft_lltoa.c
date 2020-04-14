/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 20:57:00 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/05 20:57:02 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	longlen(long long n, int base)
{
	int		len;

	len = (n < 0);
	while (n && ++len)
		n /= base;
	return (len);
}

char		*ft_lltoa(long long n, int base, int upcase)
{
	char	*s;
	int		len;

	if (base < 0 || base == 1 || base > 36)
		return (NULL);
	if (!base)
		base = 10;
	if (!(len = longlen(n, base)))
		return (ft_strdup("0"));
	upcase = upcase ? 0 : 'a' - 'A';
	if (!(s = (char*)malloc(len + 1)))
		return (NULL);
	s[len] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		s[--len] = -(n % base) + (-(n % base) < 10 ? '0' : 'A' - 10 + upcase);
		n = -(n / base);
	}
	while (n)
	{
		s[--len] = n % base + (n % base < 10 ? '0' : 'A' - 10 + upcase);
		n /= base;
	}
	return (s);
}
