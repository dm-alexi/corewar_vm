/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:30:41 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/15 01:55:18 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Read and execute instructions.
*/

#include "corewar.h"
#include "libft.h"

/*
** Cut any address to fit arena size.
*/

int			cut(int n)
{
	return (n < 0 ? n % MEM_SIZE + MEM_SIZE : n % MEM_SIZE);
}

static int	get_argtypes(t_process *t, t_vm *vm, t_byte *argtypes)
{
	int	i;
	int	sign;
	int steps;

	if (!g_tab[t->op].typebyte && (argtypes[0] = DIR_CODE))
		return (g_tab[t->op].dirsize);
	i = -1;
	sign = 1;
	steps = 1;
	while (++i < g_tab[t->op].argnum)
		if (!(argtypes[i] = (vm->arena[cut(t->pc + 1)] >> (6 - 2 * i)) & 0x03)
		|| (argtypes[i] == REG_CODE && ++steps &&
		!((g_tab[t->op].args[i] & T_REG) && vm->arena[cut(t->pc + steps)] > 0
		&& vm->arena[cut(t->pc + steps)] <= REG_NUMBER))
		|| (argtypes[i] == DIR_CODE && (steps += g_tab[t->op].dirsize) &&
		!(g_tab[t->op].args[i] & T_DIR))
		|| (argtypes[i] == IND_CODE && (steps += IND_SIZE) &&
		!(g_tab[t->op].args[i] & T_IND)))
			sign = -1;
	return (steps * sign);
}

static void	get_args(t_process *t, t_vm *vm, t_byte *argtypes, int *args)
{
	int		i;
	int		p;

	p = cut(t->pc + 2);
	i = -1;
	if (!g_tab[t->op].typebyte)
		args[0] = (g_tab[t->op].dirsize == DIR_SIZE ?
		read_dir(p - 1, vm->arena) : read_ind(p - 1, vm->arena));
	else
		while (++i < g_tab[t->op].argnum)
			if (argtypes[i] == REG_CODE)
				args[i] = vm->arena[cut(p++)];
			else if (argtypes[i] == DIR_CODE)
			{
				args[i] = (g_tab[t->op].dirsize == DIR_SIZE ?
				read_dir(p, vm->arena) : read_ind(p, vm->arena));
				p += g_tab[t->op].dirsize;
			}
			else if (argtypes[i] == IND_CODE)
			{
				args[i] = read_ind(p, vm->arena);
				p += IND_SIZE;
			}
}

void		read_instr(t_process *cur, t_vm *vm)
{
	cur->op = vm->arena[cur->pc];
	cur->exec_cycle = (cur->op > 0 && cur->op <= OP_NUM) ?
		vm->cycle + g_tab[cur->op].lag - 1 : vm->cycle;
}

void		exec_instr(t_process *cur, t_vm *vm)
{
	t_byte	argtypes[MAX_ARGS_NUMBER];
	int		args[MAX_ARGS_NUMBER];
	int		steps;

	if (cur->op > 0 && cur->op <= OP_NUM)
	{
		if ((steps = get_argtypes(cur, vm, argtypes)) > 0)
		{
			get_args(cur, vm, argtypes, args);
			g_tab[cur->op].func(cur, vm, argtypes, args);
		}
		if (g_tab[cur->op].func != zjmp)
		{
			steps = steps < 0 ? -steps : steps;
			if (vm->verbosity & MOVES)
				print_movement(vm->arena, cur->pc, steps + 1);
			cur->pc = cut(cur->pc + 1 + steps);
		}
	}
	else
		cur->pc = cut(cur->pc + 1);
}
