/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_otoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 21:31:26 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/23 23:32:16 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	olen(uintmax_t n, char **s, t_format *format)
{
	int		len;

	if (!n && format->sharp && !format->prec)
		format->prec = 1;
	len = (!n && format->prec);
	if (!n)
		format->sharp = 0;
	while (n && ++len)
		n /= 8;
	if (format->sharp && len >= format->prec)
		format->prec = len + 1;
	if (len < format->prec)
		len = format->prec;
	if (format->width < len)
		format->width = len;
	if (!(*s = (char*)malloc(format->width)))
		return (-1);
	ft_memset(*s, format->fill, format->width);
	return (len);
}

int			ft_otoa(uintmax_t n, char **s, t_format *format)
{
	int		len;
	int		tmp;

	if ((len = olen(n, s, format)) < 0)
		return (len);
	tmp = format->rpad ? len : format->width;
	if (!n && !format->sharp && format->prec--)
		(*s)[--tmp] = '0';
	while (n || format->prec > 0)
	{
		(*s)[--tmp] = n % 8 + '0';
		n /= 8;
		--(format->prec);
	}
	return (format->width);
}
