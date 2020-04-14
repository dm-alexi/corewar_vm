/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:29:23 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/12 23:58:25 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"

void	delete_vm(t_vm *vm)
{
	t_process	*t;

	while (vm->start)
	{
		t = vm->start->next;
		free(vm->start);
		vm->start = t;
	}
	free(vm->players);
}
