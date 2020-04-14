/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:22:33 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/13 00:16:29 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All arena read and write operations.
** NB: Arena is big-endian!
*/

#include "corewar.h"
#include "libft.h"

static t_process	*new_process(t_process *next, unsigned num,
	unsigned player_num, int pc)
{
	t_process	*p;

	if (!(p = (t_process*)ft_memalloc(sizeof(t_process))))
		sys_error(NULL);
	p->next = next;
	p->player_num = player_num;
	p->num = num;
	p->pc = pc;
	return (p);
}

/*
** Place champions' code in the arena and create initial processes.
*/

void				init_arena(t_vm *vm)
{
	unsigned	i;
	int			step;

	step = MEM_SIZE / vm->num_players;
	i = 0;
	while (i < vm->num_players)
	{
		ft_memcpy(vm->arena + i * step, vm->players[i].code,
		vm->players[i].header.prog_size);
		free(vm->players[i].code);
		vm->start = new_process(vm->start, ++vm->num_process,
		vm->players[i].num, i * step);
		vm->start->reg[0] = -(i + 1);
		++i;
	}
}

/*
** Read an argument of T_DIR type.
*/

int					read_dir(int start, t_byte *arena)
{
	char	s[DIR_SIZE];
	int		i;

	start = cut(start);
	i = -1;
	while (++i < DIR_SIZE)
		s[DIR_SIZE - 1 - i] = arena[(start + i) % MEM_SIZE];
	return (*((int*)s));
}

/*
** Read an argument of T_IND type.
*/

int					read_ind(int start, t_byte *arena)
{
	char	s[IND_SIZE];
	int		i;

	start = cut(start);
	i = -1;
	while (++i < IND_SIZE)
		s[IND_SIZE - 1 - i] = arena[(start + i) % MEM_SIZE];
	return (*((short*)s));
}

/*
** Write an argument to the arena.
*/

void				write_bytes(int n, int start, t_byte *arena)
{
	t_byte	*s;
	int		i;

	start = cut(start);
	s = (t_byte*)&n;
	i = -1;
	while (++i < REG_SIZE)
		arena[(start + i) % MEM_SIZE] = s[REG_SIZE - 1 - i];
}
