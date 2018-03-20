/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:07 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/20 10:52:13 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static void swaparray(struct nlist_64	*array, bool swap)
{
	if (!swap)
		return;
	array->n_value = swap_uint64(array->n_value);
	array->n_type = swap_uint64(array->n_type);
	array->n_sect = swap_uint64(array->n_sect);
	array->n_un.n_strx = swap_uint64(array->n_un.n_strx);
}

static void swapsym(struct symtab_command *sym, bool swap)
{
	if (swap)
	{
		sym->nsyms = swap_uint32(sym->nsyms);
		sym->symoff = swap_uint32(sym->symoff);
				sym->stroff = swap_uint32(sym->stroff);
	}
}

static void add_output(int nsyms, void *symoff, void *stroff, t_env* env, bool swap)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;
	t_cmd			*cmd;

	array = (void*)symoff;
	stringtable = (void*)stroff;
	cmd = NULL;
	for (i = 0; i < nsyms; ++i)
	{
		if (((void*)&array[i] + sizeof(*array) > (void*)env->end) || (void*)stringtable > (void*)env->end)
			failmessage("Please check file integrity");
		swaparray(&array[i], swap);
		mlccmd(env, array[i].n_value, typing(array[i].n_type, array[i].n_sect, env->section, array[i].n_value), stringtable + array[i].n_un.n_strx);
	}
}

void	handle_64(t_env *env, char *adr, char* max, bool swap)
{
	int 	ncmds;
	struct	mach_header_64 *header;
	struct  load_command *lc;
	int		i;
	struct symtab_command *sym;

	header = (struct mach_header_64*)adr;
	if ((void*)header > (void*)max)
		failmessage("Fail header");
	ncmds = (swap) ? swap_uint32(header->ncmds) : header->ncmds;
	lc = (struct  load_command*)(header+1);
	for (i = 0; i < ncmds; ++i)
	{
		lc->cmdsize = (swap) ? swap_uint64(lc->cmdsize) : lc->cmdsize;
		lc->cmd = (swap) ? swap_uint64(lc->cmd) : lc->cmd;
		if (lc->cmd == LC_SEGMENT_64)
			add_segment64((struct segment_command_64*)lc, env->section, swap);
		lc = (void*)lc + lc->cmdsize;
	}
	lc = (struct  load_command*)(header+1);
	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			swapsym(sym, swap);
			add_output(sym->nsyms, (void*)adr + sym->symoff, (void*)adr + sym->stroff, env, swap);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	order_cmds(env);
	print_cmds(env->list, 16);
}
