/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:56:22 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/19 11:36:32 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*t;
	char	*str;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s) + 1;
	if (!len || !(str = (char*)malloc(len)))
		return (NULL);
	t = str;
	while (*s)
		*t++ = f(*s++);
	*t = '\0';
	return (str);
}
