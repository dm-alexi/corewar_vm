/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:29:48 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/15 00:40:59 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void	and(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	int		a;
	int		b;

	if (argtypes[0] == DIR_CODE)
		a = args[0];
	else if (argtypes[0] == IND_CODE)
		a = read_dir((t->pc + args[0] % IDX_MOD), vm->arena);
	else
		a = t->reg[args[0] - 1];
	if (argtypes[1] == DIR_CODE)
		b = args[1];
	else if (argtypes[1] == IND_CODE)
		b = read_dir((t->pc + args[1] % IDX_MOD), vm->arena);
	else
		b = t->reg[args[1] - 1];
	t->reg[args[2] - 1] = a & b;
	t->carry = !t->reg[args[2] - 1];
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | and %d %d r%d\n", t->num, a, b, args[2]);
}

void	or(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	int		a;
	int		b;

	if (argtypes[0] == DIR_CODE)
		a = args[0];
	else if (argtypes[0] == IND_CODE)
		a = read_dir((t->pc + args[0] % IDX_MOD), vm->arena);
	else
		a = t->reg[args[0] - 1];
	if (argtypes[1] == DIR_CODE)
		b = args[1];
	else if (argtypes[1] == IND_CODE)
		b = read_dir((t->pc + args[1] % IDX_MOD), vm->arena);
	else
		b = t->reg[args[1] - 1];
	t->reg[args[2] - 1] = a | b;
	t->carry = !t->reg[args[2] - 1];
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | or %d %d r%d\n", t->num, a, b, args[2]);
}

void	xor(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	int		a;
	int		b;

	if (argtypes[0] == DIR_CODE)
		a = args[0];
	else if (argtypes[0] == IND_CODE)
		a = read_dir((t->pc + args[0] % IDX_MOD), vm->arena);
	else
		a = t->reg[args[0] - 1];
	if (argtypes[1] == DIR_CODE)
		b = args[1];
	else if (argtypes[1] == IND_CODE)
		b = read_dir((t->pc + args[1] % IDX_MOD), vm->arena);
	else
		b = t->reg[args[1] - 1];
	t->reg[args[2] - 1] = a ^ b;
	t->carry = !t->reg[args[2] - 1];
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | xor %d %d r%d\n", t->num, a, b, args[2]);
}

void	zjmp(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	(void)argtypes;
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | zjmp %d %s\n", t->num, args[0],
		t->carry ? "OK" : "FAILED");
	if (vm->verbosity & MOVES && !t->carry)
		print_movement(vm->arena, t->pc, 1 + g_tab[t->op].dirsize);
	t->pc = cut(t->pc +
	(t->carry ? args[0] % IDX_MOD : 1 + g_tab[t->op].dirsize));
}

void	ldi(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	int		a;
	int		b;

	if (argtypes[0] == DIR_CODE)
		a = args[0];
	else if (argtypes[0] == IND_CODE)
		a = read_dir((t->pc + args[0] % IDX_MOD), vm->arena);
	else
		a = t->reg[args[0] - 1];
	b = (argtypes[1] == DIR_CODE ? args[1] : t->reg[args[1] - 1]);
	t->reg[args[2] - 1] = read_dir((t->pc + (a + b) % IDX_MOD), vm->arena);
	if (vm->verbosity & OPERATIONS)
	{
		ft_printf("P %4u | ldi %d %d r%d\n", t->num, a, b, args[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
		a, b, a + b, t->pc + (a + b) % IDX_MOD);
	}
}
