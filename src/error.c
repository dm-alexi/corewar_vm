/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 23:32:18 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/15 02:08:59 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All error and usage messages and invariant check.
*/

#include <stdio.h>
#include <unistd.h>
#include "corewar.h"
#include "libft.h"

void	sys_error(char *s)
{
	if (!s)
		write(STDERR_FILENO, "Error: ", 7);
	perror(s);
	exit(EXIT_FAILURE);
}

void	error(char *s)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	error2(char *s, char *t)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, t, ft_strlen(t));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	ft_printf("Usage: ./corewar [[-d N | -dump N] -v N | -s] "
	"[-n N] <champion.cor> [-n N] <...>\n"
	"\t-d N\t: Dumps memory after N cycles (long format), then exits\n"
	"\t-dump N\t: Dumps memory after N cycles (short format), then exits\n"
	"\t-v N\t: Verbosity levels, can be added together to enable several\n"
	"\t\t  - 0 : Show only essentials\n"
	"\t\t  - 1 : Show lives\n"
	"\t\t  - 2 : Show cycles\n"
	"\t\t  - 4 : Show operations\n"
	"\t\t  - 8 : Show deaths\n"
	"\t\t  - 16 : Show PC movements (except for jumps)\n"
	"\t-s\t: Visualization mode\n");
	exit(EXIT_SUCCESS);
}

/*
** Check the validity of macro-defined constants
*/

void	check_invariants(void)
{
	if (OP_NUM <= 0 || SHORT_DUMP <= 0 || LONG_DUMP <= 0 ||
	SHORT_DUMP > LONG_DUMP)
		error("corewar.h constants are invalid.");
	if (IND_SIZE != sizeof(short) || REG_SIZE != sizeof(int) ||
	DIR_SIZE > REG_SIZE || REG_CODE == DIR_CODE || REG_CODE == IND_CODE ||
	DIR_CODE == IND_CODE || MEM_SIZE <= 0 || MAX_ARGS_NUMBER <= 0 ||
	MAX_ARGS_NUMBER > 4 || MAX_PLAYERS <= 0 || MEM_SIZE <= 0 ||
	CHAMP_MAX_SIZE * MAX_PLAYERS > MEM_SIZE || REG_NUMBER <= 0 ||
	CYCLE_DELTA <= 0 || T_REG == T_DIR || T_REG == T_IND || T_IND == T_DIR ||
	PROG_NAME_LENGTH < 0 || COMMENT_LENGTH < 0)
		error("op.h constants are invalid.");
}
