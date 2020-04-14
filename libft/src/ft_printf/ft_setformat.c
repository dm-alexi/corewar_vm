/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:35:48 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/28 18:35:49 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		set_specifier(const char **s, t_format *format)
{
	if (ft_strnequ(*s, "hh", 2) && (*s += 2))
		format->length = 'H';
	else if (ft_strnequ(*s, "ll", 2) && (*s += 2))
		format->length = 'L';
	else if (**s && ft_strchr("hljztL", **s))
		format->length = *((*s)++);
	if (**s && ft_strchr("bcdefginoprsuxCEFGSX%", **s))
		format->type = *((*s)++);
}

static void		set_wp(const char **s, t_format *format, va_list *va)
{
	format->prec = -1;
	if (ft_isdigit(**s))
		format->width = ft_strtol((char*)*s, (char**)s, 10);
	else if (**s == '*' && ++*s)
		format->width = va_arg(*va, int);
	if (ft_isdigit(**s))
		format->width = ft_strtol((char*)*s, (char**)s, 10);
	if (format->width < 0)
	{
		format->width = -format->width;
		format->rpad = 1;
	}
	if (**s == '.' && ++*s)
	{
		format->prec = 0;
		if (ft_isdigit(**s))
			format->prec = ft_strtol((char*)*s, (char**)s, 10);
		else if (**s == '*' && ++*s)
			format->prec = va_arg(*va, int);
		if (format->prec < 0)
			format->prec = -1;
	}
}

static void		set_flags(const char **s, t_format *format)
{
	ft_bzero(format, sizeof(t_format));
	while (**s && ft_strchr("-+ #0\'", **s))
	{
		if (**s == '-')
			format->rpad = 1;
		else if (**s == '+')
			format->sign = '+';
		else if (**s == ' ' && !format->sign)
			format->sign = ' ';
		else if (**s == '#')
			format->sharp = 1;
		else if (**s == '0')
			format->fill = '0';
		else if (**s == '\'')
			format->apost = 1;
		++*s;
	}
}

void			ft_setformat(const char **s, t_format *format, va_list *va)
{
	set_flags(s, format);
	set_wp(s, format, va);
	set_specifier(s, format);
	if (!format->fill || format->rpad ||
	(ft_strchr("diouxX", format->type) && format->prec >= 0))
		format->fill = ' ';
}
