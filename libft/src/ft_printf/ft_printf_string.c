/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:15:06 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/27 22:01:29 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int			ft_printf_pad(int fd, char c, int n)
{
	char	*s;
	int		i;

	if (n <= 0)
		return (0);
	if (!(s = (char*)malloc(n)))
	{
		i = 0;
		while (i < n)
		{
			if (write(fd, &c, 1) < 1)
				return (i);
			++i;
		}
		return (n);
	}
	ft_memset(s, c, n);
	i = write(fd, s, n);
	free(s);
	return (i);
}

int			ft_printf_char(t_format *format, va_list *va, int fd)
{
	unsigned char	c;
	int				offset;

	if (format->type == 'C' || format->length == 'l')
		return (ft_printf_wchar(format, va, fd));
	c = (unsigned char)va_arg(*va, int);
	if (format->width <= 1)
		return (write(fd, &c, 1) == 1 ? 1 : -1);
	offset = format->width - 1;
	if ((!format->rpad &&
	ft_printf_pad(fd, format->fill, offset) < offset) ||
	write(fd, &c, 1) < 1 ||
	(format->rpad && ft_printf_pad(fd, format->fill, offset) < offset))
		return (-1);
	return (format->width);
}

int			ft_printf_string(t_format *format, va_list *va, int fd)
{
	char		*s;
	int			len;
	int			offset;

	if (format->type == 'S' || format->length == 'l')
		return (ft_printf_wstring(format, va, fd));
	if (!(s = (char*)va_arg(*va, char*)))
		s = "(null)";
	len = ft_strlen(s);
	if (format->prec >= 0 && len > format->prec)
		len = format->prec;
	if (format->width <= len)
		return (write(fd, s, len) == len ? len : -1);
	offset = format->width - len;
	if ((!format->rpad && ft_printf_pad(fd, format->fill, offset) < offset) ||
	(write(fd, s, len) < len) ||
	(format->rpad && ft_printf_pad(fd, format->fill, offset) < offset))
		return (-1);
	return (format->width);
}

int			ft_printf_percent(t_format *format, int fd)
{
	int			offset;

	if (format->width <= 1)
		return (write(fd, "%", 1) == 1 ? 1 : -1);
	offset = format->width - 1;
	if ((!format->rpad && ft_printf_pad(fd, format->fill, offset) < offset) ||
	write(fd, "%", 1) < 1 ||
	(format->rpad && ft_printf_pad(fd, format->fill, offset) < offset))
		return (-1);
	return (format->width);
}
