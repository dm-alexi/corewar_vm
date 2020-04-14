/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:29:33 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/14 01:28:26 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static int		is_digital(char *s)
{
	if (!s || !*s)
		return (0);
	while (ft_isdigit(*s))
		++s;
	return (*s == '\0');
}

static int		is_flag(char *s)
{
	return (ft_strequ(s, "-d") || ft_strequ(s, "-dump") || ft_strequ(s, "-v") ||
	ft_strequ(s, "-s"));
}

/*
** Merge ordered champion list (with -n option) with the unordered one.
** Return total number of champions.
*/

static int		merge(char **files, char **unordered)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < MAX_PLAYERS && unordered[i])
	{
		while (j < MAX_PLAYERS && files[j])
			++j;
		if (j == MAX_PLAYERS)
			error("Too many champions.");
		files[j++] = unordered[i++];
	}
	while (j < MAX_PLAYERS && files[j])
		++j;
	i = j;
	while (i < MAX_PLAYERS)
		if (files[i++])
			error("Incorrect champion order.");
	return (j);
}

/*
** Execute command line option (except -n). Return number of arguments to skip.
*/

static int		exec_flag(t_vm *vm, int ac, char **av, int i)
{
	if (ft_strequ(av[i], "-d") || ft_strequ(av[i], "-dump"))
	{
		if (i == ac - 1 || !is_digital(av[i + 1]) || vm->dump_len)
			usage();
		vm->dump_len = (ft_strequ(av[i], "-d") ? LONG_DUMP : SHORT_DUMP);
		vm->dump_cycle = ft_strtol(av[i + 1], NULL, 10);
		return (2);
	}
	if (ft_strequ(av[i], "-s"))
		return ((vm->visual = 1));
	if (ft_strequ(av[i], "-v"))
	{
		if (i == ac - 1 || !is_digital(av[i + 1]) ||
		(vm->verbosity = ft_atoi(av[i + 1])) > 31)
			usage();
		return (2);
	}
	return (0);
}

/*
** Handle all command line arguments and perform full input validation.
*/

void			input(t_vm *vm, int ac, char **av)
{
	int		i;
	int		ord;
	int		tmp;
	char	*unordered[MAX_PLAYERS];
	char	*files[MAX_PLAYERS];

	i = 0;
	ord = 0;
	ft_bzero(unordered, sizeof(char*) * MAX_PLAYERS);
	ft_bzero(files, sizeof(char*) * MAX_PLAYERS);
	while (++i < ac)
		if (is_flag(av[i]))
			i += exec_flag(vm, ac, av, i) - 1;
		else if (ft_strequ(av[i], "-n"))
			i < ac - 2 && is_digital(av[++i]) && (tmp = ft_atoi(av[i])) > 0 &&
			tmp <= MAX_PLAYERS && !is_flag(av[++i]) && !files[tmp - 1] ?
			(files[tmp - 1] = av[i]) : error("Invalid player number.");
		else if (ord >= MAX_PLAYERS)
			error("Too many champions.");
		else
			unordered[ord++] = av[i];
	if (!(vm->num_players = merge(files, unordered)))
		usage();
	get_players(vm, files);
}
