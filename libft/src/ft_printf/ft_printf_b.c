/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:58:27 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/27 18:17:16 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	blen(uintmax_t n, char **s, t_format *format)
{
	int		len;

	len = !n;
	while (n && ++len)
		n /= 2;
	if (len < format->prec)
		len = format->prec;
	if (format->width < len)
		format->width = len;
	if (!(*s = (char*)malloc(format->width)))
		return (-1);
	ft_memset(*s, format->fill, format->width);
	return (len);
}

int			ft_btoa(uintmax_t n, char **s, t_format *format)
{
	int		len;
	int		tmp;

	if ((len = blen(n, s, format)) < 0)
		return (len);
	tmp = format->rpad ? len : format->width;
	if (!n && format->prec--)
		(*s)[--tmp] = '0';
	while (n || format->prec > 0)
	{
		(*s)[--tmp] = n % 2 + '0';
		n /= 2;
		--(format->prec);
	}
	return (format->width);
}
