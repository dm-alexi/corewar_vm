/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:35:24 by sscarecr          #+#    #+#             */
/*   Updated: 2020/03/15 21:52:00 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BIGINT_H
# define FT_BIGINT_H
# include <stdint.h>
# define MAX_BLOCKS 1280

typedef struct	s_bigint
{
	int			len;
	uint32_t	arr[MAX_BLOCKS];
}				t_bigint;

void			ft_bigint_copy(t_bigint *dst, const t_bigint *src);
void			ft_bigint_get(t_bigint *res, uint64_t a);
int				ft_bigint_make(t_bigint *res, int exp, uint64_t val);
void			ft_bigint_sum(t_bigint *res, const t_bigint *a,
				const t_bigint *b);

#endif
