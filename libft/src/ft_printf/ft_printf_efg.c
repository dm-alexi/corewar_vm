/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_efg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:42:57 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/27 15:43:36 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const int	g_pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000,
	10000000, 100000000, 1000000000};

static int		intlen(uint32_t n)
{
	int		i;

	i = 1;
	while ((int)n >= g_pow10[i])
		++i;
	return (i);
}

static void		get_raw_string(t_bigint *t, char *s, int len)
{
	int			i;
	int			j;
	uint32_t	n;

	j = len - (t->len - 1) * 9 - 1;
	i = t->len - 1;
	n = t->arr[i--];
	while (j >= 0)
	{
		*s++ = n / g_pow10[j];
		n %= g_pow10[j--];
	}
	while (i >= 0 && (j = 8))
	{
		n = t->arr[i--];
		while (j >= 0)
		{
			*s++ = n / g_pow10[j];
			n %= g_pow10[j--];
		}
	}
}

int				ft_round(char *s, int len, int hollow)
{
	int		i;

	if (s[i = len - hollow] > 5)
		++s[len - 1 - hollow];
	else if (s[i] == 5)
	{
		while (++i < len && !s[i])
			;
		if (i < len || s[len - 1 - hollow] % 2)
			++s[len - 1 - hollow];
	}
	i = len - 1 - hollow;
	while (i > 0 && s[i] == 10)
	{
		s[i--] = 0;
		++s[i];
	}
	if (s[0] == 10)
	{
		s[0] = 0;
		ft_memmove(s + 1, s, len - hollow);
		s[0] = 1;
		++len;
	}
	return (len - hollow);
}

int				ft_printf_efg(t_format *format, t_bigint *t, int exp, char **s)
{
	char	*str;
	int		len;

	len = (t->len - 1) * 9 + intlen(t->arr[t->len - 1]);
	if (!(str = (char*)malloc(len)))
		return (-1);
	get_raw_string(t, str, len);
	if (((format->type == 'f' || format->type == 'F') &&
	(((len = ft_process_f(&str, exp, len, format->prec)) < 0) ||
	(len = ft_printf_f(format, len, str, s)) < 0)) ||
	((format->type == 'e' || format->type == 'E') &&
	(((len = ft_process_e(&str, -exp, len, format)) < 0) ||
	(len = ft_printf_e(format, len, str, s)) < 0)) ||
	(((format->type == 'g' || format->type == 'G') &&
	(-exp + len - 1 < -4 || -exp + len - 1 >= format->prec)) &&
	(((len = ft_process_ge(&str, -exp, len, format)) < 0) ||
	(len = ft_printf_e(format, len, str, s)) < 0)) ||
	(((format->type == 'g' || format->type == 'G') &&
	!(-exp + len - 1 < -4 || -exp + len - 1 >= format->prec)) &&
	(((len = ft_process_gf(&str, exp, len, format)) < 0) ||
	(len = ft_printf_f(format, len, str, s)) < 0)))
		len = -1;
	free(str);
	return (len);
}
