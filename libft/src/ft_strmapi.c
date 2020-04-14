/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:57:15 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/19 11:36:23 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;
	size_t	len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s) + 1;
	if (!len || !(str = (char*)malloc(len)))
		return (NULL);
	i = 0;
	while (*s)
	{
		*(str + i) = f(i, *s++);
		++i;
	}
	*(str + i) = '\0';
	return (str);
}
