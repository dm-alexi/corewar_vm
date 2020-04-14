/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:22:02 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/27 15:18:28 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	float_zero_e(t_format *format, char **s)
{
	int		len;
	int		tmp;

	len = 5 + (format->sign != 0) + (format->sharp ? format->prec + 1 : 0);
	if (len > format->width)
		format->width = len;
	if (!(*s = (char*)malloc(format->width)))
		return (-1);
	ft_memset(*s, format->fill, format->width);
	tmp = (format->sign != 0) + (format->rpad ? 0 : format->width - len);
	if (format->sign)
		(*s)[**s == '0' || format->rpad ? 0 : tmp - 1] = format->sign;
	(*s)[tmp++] = '0';
	if (format->sharp)
		(*s)[tmp++] = '.';
	while (format->prec-- > 0)
		(*s)[tmp++] = '0';
	(*s)[tmp++] = format->type;
	ft_memcpy(*s + tmp, "+00", 3);
	return (format->width);
}

static int	float_zero_fg(t_format *format, char **s)
{
	int		len;

	if ((format->type == 'G' || format->type == 'g') && format->prec)
		format->prec = format->sharp ? format->prec - 1 : 0;
	if (format->prec)
		format->sharp = 1;
	len = 1 + (format->sign != 0) + (format->sharp ? format->prec + 1 : 0);
	if (len > format->width)
		format->width = len;
	if (!(*s = (char*)malloc(format->width)))
		return (-1);
	ft_memset(*s, format->fill, format->width);
	len = format->rpad ? len : format->width;
	while (format->prec-- > 0)
		(*s)[--len] = '0';
	if (format->sharp)
		(*s)[--len] = '.';
	(*s)[--len] = '0';
	len = **s == '0' ? 0 : len - 1;
	if (format->sign)
		(*s)[len] = format->sign;
	return (format->width);
}

static int	float_special(t_format *format, char **s, uint64_t val)
{
	int		len;
	char	*mes;

	if (val == 0x8000000000000000)
		mes = ft_isupper(format->type) ? "INF" : "inf";
	else
	{
		mes = ft_isupper(format->type) ? "NAN" : "nan";
		format->sign = 0;
	}
	len = 3 + (format->sign != 0);
	if (format->width < len)
		format->width = len;
	if (!(*s = (char*)malloc(format->width)))
		return (-1);
	ft_memset(*s, ' ', format->width);
	len = (format->rpad ? len : format->width) - 3;
	ft_memcpy(*s + len, mes, 3);
	if (format->sign)
		(*s)[len - 1] = format->sign;
	return (format->width);
}

static int	floatlen(long double d, t_format *format, char **s)
{
	uint64_t	val;
	uint32_t	exp;
	int			exp10;
	t_bigint	t;

	val = *((uint64_t*)&d);
	exp = (uint32_t)(*((uint64_t*)&d + 1)) & 0x00007fff;
	if ((uint32_t)((*((uint64_t*)&d + 1)) & 0x00008000) > 0)
		format->sign = '-';
	if (!val && (format->type == 'e' || format->type == 'E'))
		return (float_zero_e(format, s));
	if (!val)
		return (float_zero_fg(format, s));
	if (exp == 0x00007fff)
		return (float_special(format, s, val));
	exp10 = ft_bigint_make(&t, (int)exp - 16446, val);
	return (ft_printf_efg(format, &t, exp10, s));
}

int			ft_printf_float(t_format *format, va_list *va, int fd)
{
	long double		d;
	char			*s;
	int				len;

	d = (format->length == 'L') ?
		va_arg(*va, long double) : (long double)va_arg(*va, double);
	if (format->prec < 0)
		format->prec = 6;
	if (format->prec > 0 && format->type != 'g' && format->type != 'G')
		format->sharp = 1;
	if (!format->prec && (format->type == 'g' || format->type == 'G'))
		format->prec = 1;
	s = NULL;
	if ((len = floatlen(d, format, &s)) < 0)
		return (-1);
	if (write(fd, s, len) < len)
		len = -1;
	free(s);
	return (len);
}
