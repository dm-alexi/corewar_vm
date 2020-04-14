/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xtoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 22:01:10 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/23 23:35:37 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	xlen(uintmax_t n, char **s, t_format *format)
{
	int		len;
	int		preflen;

	preflen = (format->sharp ? 2 : 0);
	len = (!n && format->prec);
	while (n && ++len)
		n /= 16;
	if (len < format->prec)
		len = format->prec;
	len += preflen;
	if (format->width < len)
		format->width = len;
	if (!(*s = (char*)malloc(format->width)))
		return (-1);
	ft_memset(*s, format->fill, format->width);
	return (len);
}

int			ft_xtoa(uintmax_t n, char **s, t_format *format)
{
	int		len;
	int		tmp;
	int		digit;
	char	*pref;

	if (!n)
		format->sharp = 0;
	pref = format->type == 'X' ? "0X" : "0x";
	if ((len = xlen(n, s, format)) < 0)
		return (len);
	tmp = format->rpad ? len : format->width;
	if (!n && format->prec--)
		(*s)[--tmp] = '0';
	while (n || format->prec > 0)
	{
		if ((digit = n % 16) < 10)
			(*s)[--tmp] = digit + '0';
		else
			(*s)[--tmp] = digit - 10 + (format->type == 'X' ? 'A' : 'a');
		n /= 16;
		--(format->prec);
	}
	if (format->sharp)
		ft_memcpy(**s == '0' ? *s : *s + tmp - 2, pref, 2);
	return (format->width);
}
