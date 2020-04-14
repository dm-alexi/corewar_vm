/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:36:31 by sscarecr          #+#    #+#             */
/*   Updated: 2020/03/15 21:51:39 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bigint.h"

void	ft_bigint_get(t_bigint *res, uint64_t a)
{
	if (a)
	{
		res->len = 0;
		while (a)
		{
			res->arr[res->len++] = a % 1000000000;
			a /= 1000000000;
		}
	}
	else
	{
		res->arr[0] = 0;
		res->len = 1;
	}
}

void	ft_bigint_copy(t_bigint *dst, const t_bigint *src)
{
	int		i;

	i = 0;
	while (i < src->len)
	{
		dst->arr[i] = src->arr[i];
		++i;
	}
	dst->len = src->len;
}

void	ft_bigint_sum(t_bigint *res, const t_bigint *a, const t_bigint *b)
{
	int			i;
	uint64_t	carry;
	uint64_t	sum;

	if (a->len <= b->len)
	{
		i = 0;
		carry = 0;
		while (i < a->len)
		{
			sum = carry + (uint64_t)a->arr[i] + (uint64_t)b->arr[i];
			res->arr[i++] = sum % 1000000000;
			carry = sum / 1000000000;
		}
		while (i < b->len)
		{
			sum = carry + (uint64_t)b->arr[i];
			res->arr[i++] = sum % 1000000000;
			carry = sum / 1000000000;
		}
		res->arr[i] = carry;
		res->len = carry ? i + 1 : i;
	}
	else
		ft_bigint_sum(res, b, a);
}
