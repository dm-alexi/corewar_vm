/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:14:16 by sscarecr          #+#    #+#             */
/*   Updated: 2019/10/28 18:37:20 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int		print_formatted(const char **s, va_list *va, int n, int fd)
{
	t_format	format;

	ft_setformat(s, &format, va);
	if (!format.type)
		return (0);
	if (format.type == '%')
		return (ft_printf_percent(&format, fd));
	if (format.type == 'c' || format.type == 'C')
		return (ft_printf_char(&format, va, fd));
	if (format.type == 's' || format.type == 'S')
		return (ft_printf_string(&format, va, fd));
	if (format.type == 'd' || format.type == 'i')
		return (ft_printf_int(&format, va, fd));
	if (ft_strchr("buoxX", format.type))
		return (ft_printf_uint(&format, va, fd));
	if (format.type == 'p')
		return (ft_printf_ptr(&format, va, fd));
	if (ft_strchr("efgEFG", format.type))
		return (ft_printf_float(&format, va, fd));
	if (format.type == 'r')
		return (ft_printf_r(&format, va, fd));
	if (format.type == 'n')
		return (ft_printf_n(va, n));
	return (0);
}

int		ft_printf(const char *line, ...)
{
	int				n;
	int				count;
	va_list			va;
	const char		*s;

	n = 0;
	va_start(va, line);
	s = line;
	while (*line)
	{
		while (*s && *s != '%')
			++s;
		n += s - line;
		write(1, line, s - line);
		if (*s)
		{
			++s;
			if ((count = print_formatted(&s, &va, n, 1)) < 0)
				return (-1);
			n += count;
		}
		line = s;
	}
	va_end(va);
	return (n);
}

int		ft_dprintf(int fd, const char *line, ...)
{
	int				n;
	int				count;
	va_list			va;
	const char		*s;

	n = 0;
	va_start(va, line);
	s = line;
	while (*line)
	{
		while (*s && *s != '%')
			++s;
		n += s - line;
		write(fd, line, s - line);
		if (*s)
		{
			++s;
			if ((count = print_formatted(&s, &va, n, fd)) < 0)
				return (-1);
			n += count;
		}
		line = s;
	}
	va_end(va);
	return (n);
}
