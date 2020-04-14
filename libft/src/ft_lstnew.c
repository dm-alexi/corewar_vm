/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 11:34:27 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/07 11:34:30 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*t;

	if (!(t = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	t->next = NULL;
	if (content && content_size)
	{
		if (!(t->content = malloc(content_size)))
		{
			free(t);
			return (NULL);
		}
		t->content_size = content_size;
		ft_memcpy(t->content, content, content_size);
	}
	else
	{
		t->content = NULL;
		t->content_size = 0;
	}
	return (t);
}
