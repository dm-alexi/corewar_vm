/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:46:55 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/25 22:50:40 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	cut_tail(char *s, int total)
{
	while (s[total - 1] == '0')
		--total;
	if (s[total - 1] == '.')
		--total;
	return (total);
}

static int	add_sign_width(t_format *format, int len, char **s)
{
	char	*tmp;
	int		total;

	total = len + (format->sign != 0);
	if (format->width > total)
		total = format->width;
	if (total == len)
		return (len);
	if (!(tmp = (char*)malloc(total)))
		return (-1);
	ft_memset(tmp, format->fill, total);
	ft_memcpy(tmp + (format->rpad ?
		(format->sign != 0) : total - len), *s, len);
	if (format->sign)
		tmp[*tmp == '0' || format->rpad ? 0 : total - len - 1] = format->sign;
	free(*s);
	*s = tmp;
	return (total);
}

int			ft_process_f(char **s, int exp, int len, int prec)
{
	char	*str;
	int		total;

	total = exp + 1 > len ? exp + 1 : len;
	if (prec > exp)
		total += prec - exp;
	if (total > len)
	{
		if (!(str = ft_memalloc(total)))
			return (-1);
		ft_memcpy(str + (exp + 1 > len ? exp + 1 - len : 0), *s, len);
		free(*s);
		*s = str;
	}
	if (prec < exp)
		total = ft_round(*s, total, exp - prec);
	return (total);
}

int			ft_process_gf(char **s, int exp, int len, t_format *format)
{
	char	*str;
	int		total;
	int		tmp;

	format->prec -= len - exp;
	total = exp + 1 > len ? exp + 1 : len;
	if (format->prec > exp)
		total += format->prec - exp;
	if (total > len)
	{
		if (!(str = ft_memalloc(total)))
			return (-1);
		ft_memcpy(str + (exp + 1 > len ? exp + 1 - len : 0), *s, len);
		free(*s);
		*s = str;
	}
	if (format->prec < exp)
	{
		tmp = ft_round(*s, total, exp - format->prec);
		if ((total -= exp - format->prec) < tmp)
			--(format->prec);
	}
	return (total);
}

int			ft_printf_f(t_format *format, int len, char *str, char **s)
{
	int		total;
	int		i;
	int		j;

	i = 0;
	while (i < len)
		str[i++] += '0';
	total = len + (format->sharp || format->prec) +
		(format->apost ? (len - format->prec - 1) / 3 : 0);
	if (!((*s) = (char*)malloc(total)))
		return (-1);
	j = len - format->prec;
	ft_memcpy(*s + total - format->prec, str + j, format->prec);
	if (format->sharp || format->prec)
		(*s)[total - format->prec - 1] = '.';
	i = total - format->prec - 1 - (format->sharp || format->prec);
	while (--j >= 0)
	{
		(*s)[i--] = str[j];
		if (format->apost && !((len - format->prec - j) % 3))
			(*s)[i--] = '\'';
	}
	if (ft_toupper(format->type) == 'G' && format->prec && !format->sharp)
		total = cut_tail(*s, total);
	return (add_sign_width(format, total, s));
}
