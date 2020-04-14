/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:50:32 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/10 20:09:13 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*s;
	size_t	len;

	len = ft_strlen(src) + 1;
	if (!len || !(s = (char*)malloc(len)))
		return (NULL);
	return (ft_strcpy(s, src));
}
