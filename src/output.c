/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:30:27 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/15 02:08:23 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All basic output messages and dump.
*/

#ifdef _WIN32
# include <stdio.h>
#endif
#include <unistd.h>
#include "libft.h"
#include "corewar.h"

void		introduce(t_vm *vm)
{
	unsigned	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i < vm->num_players)
	{
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
		i + 1, vm->players[i].header.prog_size, vm->players[i].header.prog_name,
		vm->players[i].header.comment);
		++i;
	}
}

void		declare_winner(t_vm *vm)
{
	ft_printf(COPYCAT ? "Contestant %u, \"%s\", has won !\n" :
	"Player %u (%s) won\n",
	vm->last_alive, vm->players[vm->last_alive - 1].header.prog_name);
}

void		print_movement(t_byte *arena, int pc, int n)
{
	char	line[7 + 3 * REG_SIZE * MAX_ARGS_NUMBER];
	t_byte	t;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < n)
	{
		t = *(arena + (pc + i) % MEM_SIZE);
		line[j++] = (t / 16 > 9 ? t / 16 - 10 + 'a' : t / 16 + '0');
		line[j++] = (t % 16 > 9 ? t % 16 - 10 + 'a' : t % 16 + '0');
		line[j++] = ' ';
		++i;
	}
	line[j] = '\0';
	ft_printf("ADV %d (0x%04x -> 0x%04x) %s\n", n, pc, pc + n, line);
}

int			dump(t_vm *vm)
{
	t_byte	*t;
	char	str[LONG_DUMP * 3 + 1];
	char	*s;

	t = vm->arena;
	while (t - vm->arena < MEM_SIZE)
	{
		ft_printf("0x%04x : ", t - vm->arena);
		s = str;
		while (t != vm->arena + MEM_SIZE)
		{
			*s++ = (*t / 16 > 9 ? *t / 16 - 10 + 'a' : *t / 16 + '0');
			*s++ = (*t % 16 > 9 ? *t % 16 - 10 + 'a' : *t % 16 + '0');
			*s++ = ' ';
			if ((++t - vm->arena) % vm->dump_len == 0)
				break ;
		}
		*s++ = '\n';
		write(STDOUT_FILENO, str, s - str);
	}
	return (0);
}
