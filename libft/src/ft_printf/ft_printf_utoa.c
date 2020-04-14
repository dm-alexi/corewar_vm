/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:31:26 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/23 22:49:50 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ulen(uintmax_t n, char **s, t_format *format)
{
	int		len;
	int		apostrophes;

	len = (!n && format->prec);
	apostrophes = 0;
	while (n && ++len)
		n /= 10;
	if (format->apost && len > 3)
		apostrophes = (len - 1) / 3;
	if (len < format->prec)
		len = format->prec;
	len += apostrophes;
	if (format->width < len)
		format->width = len;
	if (!(*s = (char*)malloc(format->width)))
		return (-1);
	ft_memset(*s, format->fill, format->width);
	return (len);
}

int			ft_utoa(uintmax_t n, char **s, t_format *format)
{
	int		len;
	int		tmp;
	int		count;

	if ((len = ulen(n, s, format)) < 0)
		return (len);
	tmp = format->rpad ? len : format->width;
	count = 0;
	if (!n && format->prec--)
		(*s)[--tmp] = '0';
	while (n || format->prec > 0)
	{
		(*s)[--tmp] = n % 10 + '0';
		n /= 10;
		if (format->apost && !(++count % 3))
			(*s)[--tmp] = '\'';
		--(format->prec);
	}
	return (format->width);
}
