/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:29:43 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/13 22:43:31 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void	live(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	(void)argtypes;
	t->last_live = vm->cycle;
	++vm->live_calls;
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | live %d\n", t->num, args[0]);
	if (-args[0] > 0 && (unsigned)(-args[0]) <= vm->num_players)
	{
		vm->last_alive = vm->players[-args[0] - 1].num;
		if (vm->verbosity & LIVES)
			ft_printf(COPYCAT ? "Player %u (%s) is said to be alive\n" :
			"A process shows that player %u (%s) is alive\n",
			-args[0], vm->players[-args[0] - 1].header.prog_name);
	}
}

void	ld(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	t->reg[args[1] - 1] = (argtypes[0] == DIR_CODE ? args[0] :
	read_dir(t->pc + args[0] % IDX_MOD, vm->arena));
	t->carry = !t->reg[args[1] - 1];
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | ld %d r%d\n", t->num, t->reg[args[1] - 1], args[1]);
}

void	st(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	if (argtypes[1] == IND_CODE)
		write_bytes(t->reg[args[0] - 1], t->pc + args[1] % IDX_MOD, vm->arena);
	else
		t->reg[args[1] - 1] = t->reg[args[0] - 1];
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | st r%d %d\n", t->num, args[0], args[1]);
}

void	add(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	(void)argtypes;
	t->reg[args[2] - 1] = t->reg[args[0] - 1] + t->reg[args[1] - 1];
	t->carry = !t->reg[args[2] - 1];
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | add r%d r%d r%d\n", t->num, args[0], args[1],
		args[2]);
}

void	sub(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	(void)argtypes;
	t->reg[args[2] - 1] = t->reg[args[0] - 1] - t->reg[args[1] - 1];
	t->carry = !t->reg[args[2] - 1];
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | sub r%d r%d r%d\n", t->num, args[0], args[1],
		args[2]);
}
