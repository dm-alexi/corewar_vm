/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 11:34:58 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/12 19:05:25 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*t;
	t_list	*s;
	t_list	*tmp;

	if (!lst || !f || !(tmp = f(lst)) ||
		!(t = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	s = t;
	while (lst->next && (tmp = f(lst->next)) &&
		(s->next = ft_lstnew(tmp->content, tmp->content_size)))
	{
		s = s->next;
		lst = lst->next;
	}
	if (lst->next)
		while (t)
		{
			tmp = t->next;
			free(t->content);
			free(t);
			t = tmp;
		}
	return (t);
}
