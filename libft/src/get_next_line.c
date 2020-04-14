/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:54:58 by sscarecr          #+#    #+#             */
/*   Updated: 2019/12/17 19:29:52 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

/*
** Fills the buffer by repeatedly reading BUFF_SIZE bytes from a give file,
** stops at encountering '\n'. Returns the size of a string needed to contain
** the resulting line, including the terminating '\0'. In case of a read() error
** returns -1. If the end of file is reached and no data is read, returns 0.
*/

static int		fillbuf(const int fd, t_buf *buf)
{
	int		len;
	char	*s;

	if (!buf->len)
	{
		buf->offset = buf->str;
		if ((buf->len = read(fd, buf->str, BUFF_SIZE)) <= 0)
			return (buf->len);
	}
	len = 0;
	while (!(s = (char*)ft_memchr(buf->offset, '\n', buf->len)))
	{
		len += buf->len;
		buf->next = (t_buf*)malloc(sizeof(t_buf));
		buf = buf->next;
		buf->next = NULL;
		buf->offset = buf->str;
		if ((buf->len = read(fd, buf->str, BUFF_SIZE)) == -1)
			return (-1);
		else if (buf->len == 0)
			break ;
	}
	if (s)
		len += s - buf->offset;
	return (len + 1);
}

/*
** Calls fillbuf(), allocates memory for a line, copies the line and rearranges
** the buffer. If read() or malloc() error occurs, returns -1. If the buffer
** is empty and the end of file is reached, returns 0.
*/

static int		readbuf(const int fd, t_file *f, char **line)
{
	char	*s;
	t_buf	*tmp;
	int		len;

	if ((len = fillbuf(fd, f->arr[fd])) <= 0)
		return (len);
	if (!(*line = (char*)malloc(len)))
		return (-1);
	s = *line;
	*(s + len - 1) = '\0';
	while ((tmp = f->arr[fd]->next))
	{
		ft_memcpy(s, f->arr[fd]->offset, f->arr[fd]->len);
		s += f->arr[fd]->len;
		len -= f->arr[fd]->len;
		free(f->arr[fd]);
		f->arr[fd] = tmp;
	}
	ft_memcpy(s, f->arr[fd]->offset, len - 1);
	f->arr[fd]->offset += len;
	f->arr[fd]->len = f->arr[fd]->len > len ? f->arr[fd]->len - len : 0;
	return (1);
}

/*
** Deletes a file descriptor from the array f.arr. If possible, reallocates
** the array to a minimum size necessary.
*/

static void		delfile(int fd, t_file *f)
{
	t_buf	*t;
	t_buf	**tmp;

	while ((t = f->arr[fd]))
	{
		f->arr[fd] = f->arr[fd]->next;
		free(t);
	}
	if (fd == f->len - 1)
	{
		while (fd >= 0 && !f->arr[fd])
			--fd;
		if (fd < 0)
		{
			free(f->arr);
			f->arr = NULL;
		}
		else if ((tmp = ft_realloc(f->arr, f->len * sizeof(t_buf*),
		(fd + 1) * sizeof(t_buf*))))
			f->arr = tmp;
		f->len = fd + 1;
	}
}

/*
** Expands the array f.arr to include newly added file descriptor.
** Upon successful execution returns 0, otherwise 1.
*/

static int		expand(const int fd, t_file *f)
{
	size_t	size;
	t_buf	**tmp;

	size = (fd + 1) * sizeof(t_buf*);
	if (!(tmp = (t_buf**)ft_realloc(f->arr, f->len * sizeof(t_buf*), size)))
		return (1);
	ft_bzero(tmp + f->len, size - f->len * sizeof(t_buf*));
	f->arr = tmp;
	f->len = fd + 1;
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_file	f;
	int				r;

	if (fd < 0 || !line || (fd >= f.len && expand(fd, &f)))
		return (-1);
	if (!f.arr[fd])
	{
		if (!(f.arr[fd] = (t_buf*)malloc(sizeof(t_buf))))
			return (-1);
		f.arr[fd]->next = NULL;
		f.arr[fd]->len = 0;
		f.arr[fd]->offset = f.arr[fd]->str;
	}
	if ((r = readbuf(fd, &f, line)) <= 0)
		delfile(fd, &f);
	return (r);
}
