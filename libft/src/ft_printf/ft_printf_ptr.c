/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:21:27 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/23 19:03:40 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int		ptrlen(uintptr_t p, char **s, t_format *format)
{
	int		len;

	len = 2 + (!p && format->prec);
	while (p && ++len)
		p /= 16;
	if (len < format->prec + 2)
		len = format->prec + 2;
	if (format->prec < len)
		format->prec = len;
	if (format->width < len)
		format->width = len;
	if (!(*s = (char*)malloc(format->width)))
		return (-1);
	ft_memset(*s, format->fill, format->width);
	return (len);
}

int				ft_printf_ptr(t_format *format, va_list *va, int fd)
{
	uintptr_t	p;
	int			len;
	int			tmp;
	int			digit;
	char		*s;

	p = (uintptr_t)va_arg(*va, void*);
	if ((len = ptrlen(p, &s, format)) < 0)
		return (-1);
	tmp = format->rpad ? len : format->width;
	while (p || format->prec > 0)
	{
		digit = p % 16;
		s[--tmp] = digit + (digit < 10 ? '0' : 'a' - 10);
		p /= 16;
		--(format->prec);
	}
	s[*s == '0' ? 1 : tmp + 1] = 'x';
	if (write(fd, s, format->width) < format->width)
		format->width = -1;
	free(s);
	return (format->width);
}
