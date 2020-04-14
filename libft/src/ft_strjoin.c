/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:54:23 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/15 15:15:35 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*t;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 + len2 < len1 || !(len1 + len2 + 1) ||
	!(str = (char*)malloc(len1 + len2 + 1)))
		return (NULL);
	t = str;
	while (*s1)
		*t++ = *s1++;
	while ((*t++ = *s2++))
		;
	return (str);
}
