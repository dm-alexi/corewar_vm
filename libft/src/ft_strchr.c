/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:46:24 by sscarecr          #+#    #+#             */
/*   Updated: 2019/09/05 21:46:57 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *str, int val)
{
	char	c;

	c = (char)val;
	while (*str != c && *str)
		++str;
	return (*str == c ? (char *)str : NULL);
}
