/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscarecr <sscarecr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 16:28:58 by sscarecr          #+#    #+#             */
/*   Updated: 2020/04/15 01:53:56 by sscarecr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"

/*
** In COPYCAT mode all the 'general' messages from zaz's Corewar are reproduced.
** NB: it doesn't comply with the subject!
*/

# define COPYCAT		0

# define OP_NUM			16
# define SHORT_DUMP		32
# define LONG_DUMP		64

# define LIVES			1
# define CYCLES			2
# define OPERATIONS		4
# define DEATHS			8
# define MOVES			16

typedef unsigned char	t_byte;

typedef struct	s_player
{
	t_header	header;
	t_byte		*code;
	unsigned	num;
}				t_player;

typedef struct	s_process
{
	unsigned			num;
	unsigned			last_live;
	t_byte				carry;
	t_byte				op;
	int					pc;
	int					reg[REG_NUMBER];
	struct s_process	*next;
	unsigned			player_num;
	unsigned			exec_cycle;
}				t_process;

typedef struct	s_vm
{
	t_byte		arena[MEM_SIZE];
	unsigned	num_players;
	t_player	*players;
	unsigned	num_process;
	t_process	*start;
	unsigned	cycle;
	int			cycles_to_die;
	unsigned	checks;
	unsigned	next_check;
	unsigned	live_calls;
	unsigned	last_alive;
	unsigned	dump_cycle;
	unsigned	dump_len;
	unsigned	verbosity;
	t_byte		visual;
}				t_vm;

typedef struct	s_op
{
	void	(*func)(t_process*, t_vm*, t_byte *argtypes, int* args);
	t_byte	typebyte;
	int		argnum;
	char	args[3];
	int		dirsize;
	int		lag;
}				t_op;

extern const t_op	g_tab[];

void			sys_error(char *s);
void			error(char *s);
void			error2(char *s, char *t);
void			usage(void);
void			check_invariants(void);

void			input(t_vm *vm, int ac, char **av);
void			get_players(t_vm *vm, char **files);

void			introduce(t_vm *vm);
void			declare_winner(t_vm *vm);
void			print_movement(t_byte *arena, int pc, int n);
int				dump(t_vm *vm);

int				cut(int n);
void			init_arena(t_vm *vm);
int				read_dir(int start, t_byte *arena);
int				read_ind(int start, t_byte *arena);
void			write_bytes(int n, int start, t_byte *arena);
int				battle(t_vm *vm);
void			read_instr(t_process *cur, t_vm *vm);
void			exec_instr(t_process *cur, t_vm *vm);
void			delete_vm(t_vm *vm);

void			live(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			ld(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			st(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			add(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			sub(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			and(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			or(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			xor(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			zjmp(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			ldi(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			sti(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			sfork(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			lld(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			lldi(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			lfork(t_process *t, t_vm *vm, t_byte *argtypes, int *args);
void			aff(t_process *t, t_vm *vm, t_byte *argtypes, int *args);

#endif
