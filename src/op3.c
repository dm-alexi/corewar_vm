/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:29:53 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/13 22:45:01 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void	sti(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	int		a;
	int		b;

	if (argtypes[1] == DIR_CODE)
		a = args[1];
	else if (argtypes[1] == IND_CODE)
		a = read_dir((t->pc + args[1] % IDX_MOD), vm->arena);
	else
		a = t->reg[args[1] - 1];
	b = (argtypes[2] == DIR_CODE ? args[2] : t->reg[args[2] - 1]);
	write_bytes(t->reg[args[0] - 1], t->pc + (a + b) % IDX_MOD, vm->arena);
	if (vm->verbosity & OPERATIONS)
	{
		ft_printf("P %4u | sti r%d %d %d\n", t->num, args[0], a, b);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		a, b, a + b, t->pc + (a + b) % IDX_MOD);
	}
}

void	sfork(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	t_process	*p;

	(void)argtypes;
	if (!(p = (t_process*)ft_memalloc(sizeof(t_process))))
		sys_error(NULL);
	ft_memcpy(p, t, sizeof(t_process));
	p->num = ++vm->num_process;
	p->pc = cut(t->pc + args[0] % IDX_MOD);
	p->next = vm->start;
	vm->start = p;
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | fork %d (%d)\n", t->num, args[0],
		t->pc + args[0] % IDX_MOD);
}

/*
** Original corewar reads 2 bytes here instead of 4, which is probably a bug.
** Function below reproduces this behavior. Substitute read_ind(...) with
** read_dir(...) to 'fix' it.
*/

void	lld(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	t->reg[args[1] - 1] = (argtypes[0] == DIR_CODE ? args[0] :
	read_ind(t->pc + args[0], vm->arena));
	t->carry = !t->reg[args[1] - 1];
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | lld %d r%d\n", t->num, t->reg[args[1] - 1], args[1]);
}

void	lldi(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	int		a;
	int		b;

	if (argtypes[0] == DIR_CODE)
		a = args[0];
	else if (argtypes[0] == IND_CODE)
		a = read_dir(t->pc + args[0] % IDX_MOD, vm->arena);
	else
		a = t->reg[args[0] - 1];
	b = (argtypes[1] == DIR_CODE ? args[1] : t->reg[args[1] - 1]);
	t->reg[args[2] - 1] = read_dir(t->pc + a + b, vm->arena);
	t->carry = !t->reg[args[2] - 1];
	if (vm->verbosity & OPERATIONS)
	{
		ft_printf("P %4u | lldi %d %d r%d\n", t->num, a, b, args[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
		a, b, a + b, t->pc + a + b);
	}
}

void	lfork(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	t_process	*p;

	(void)argtypes;
	if (!(p = (t_process*)ft_memalloc(sizeof(t_process))))
		sys_error(NULL);
	ft_memcpy(p, t, sizeof(t_process));
	p->num = ++vm->num_process;
	p->pc = cut(t->pc + args[0]);
	p->next = vm->start;
	vm->start = p;
	if (vm->verbosity & OPERATIONS)
		ft_printf("P %4u | lfork %d (%d)\n", t->num, args[0], t->pc + args[0]);
}
