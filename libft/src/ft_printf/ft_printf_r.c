/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:49:53 by sscarecr          #+#    #+#             */
/*   Updated: 2019/11/02 17:23:55 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static void		put_char(char **dst, char *src)
{
	unsigned char	c;

	if (ft_isprint(*src))
		*((*dst)++) = *src;
	else
	{
		c = (unsigned char)*src;
		*((*dst)++) = '\\';
		*((*dst)++) = c / 100 + '0';
		*((*dst)++) = (c % 100) / 10 + '0';
		*((*dst)++) = c % 10 + '0';
	}
}

static int		get_rline(t_format *format, char **s)
{
	char	*tmp;
	char	*str;
	char	*t;
	int		len;

	if (format->prec < 0)
		format->prec = ft_strlen(*s);
	tmp = *s;
	len = 0;
	while (tmp - *s < format->prec)
		len += ft_isprint(*tmp++) ? 1 : 4;
	if (format->width < len)
		format->width = len;
	if (!(str = (char*)malloc(format->width)))
		return (-1);
	ft_memset(str, format->fill, format->width);
	tmp = *s;
	t = str + (format->rpad ? 0 : format->width - len);
	while (tmp - *s < format->prec)
		put_char(&t, tmp++);
	*s = str;
	return (format->width);
}

int				ft_printf_r(t_format *format, va_list *va, int fd)
{
	char	*s;
	int		len;

	if (!(s = (char*)va_arg(*va, char*)))
		s = "(null)";
	if ((len = get_rline(format, &s)) < 0)
		return (-1);
	if (write(fd, s, len) < len)
		len = -1;
	free(s);
	return (len);
}
