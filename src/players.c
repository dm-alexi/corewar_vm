/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:30:35 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/26 16:09:38 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Read champion files and perform data validation.
** NB: Champion files are big-endian!
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "corewar.h"

static void	byte_swap(unsigned *n)
{
	int		i;
	char	*s;
	char	c;

	i = 0;
	s = (char*)n;
	while (i < (int)sizeof(unsigned) / 2)
	{
		c = s[i];
		s[i] = s[sizeof(unsigned) - 1 - i];
		s[sizeof(unsigned) - 1 - i] = c;
		++i;
	}
}

static void	get_player(t_player *player, char *file)
{
	int	fd;
	int	r;

	r = 0;
	if ((fd = open(file, O_RDONLY)) < 0 ||
	(r = read(fd, &(player->header), sizeof(t_header))) < 0)
		sys_error(file);
	byte_swap(&player->header.magic);
	byte_swap(&player->header.prog_size);
	if (r < (int)sizeof(t_header) || player->header.magic != COREWAR_EXEC_MAGIC)
		error2(file, " has an invalid header.");
	if (player->header.prog_size > CHAMP_MAX_SIZE)
		error2(file, " code size exceeds maximum value.");
	if (!(player->code = (t_byte*)malloc(player->header.prog_size + 1)))
		sys_error(NULL);
	if ((r = read(fd, player->code, player->header.prog_size + 1)) !=
	(int)player->header.prog_size)
		r < 0 ? sys_error(file) : error2(file, " has a wrong code size.");
	close(fd);
}

void		get_players(t_vm *vm, char **files)
{
	unsigned	i;

	if (!(vm->players = (t_player*)malloc(sizeof(t_player) * vm->num_players)))
		sys_error(NULL);
	i = 0;
	while (i < vm->num_players)
	{
		get_player(vm->players + i, files[i]);
		vm->players[i].num = i + 1;
		++i;
	}
}
