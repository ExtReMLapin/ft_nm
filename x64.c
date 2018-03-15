/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:07 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/15 11:01:52 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static void add_output(int nsyms, void *symoff, void *stroff, t_env* env)
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
		if (lc->cmd == LC_SEGMENT_64)
			add_segment64((struct segment_command_64*)lc, env->section );
		lc = (void*)lc + lc->cmdsize;
	}

	lc = (struct  load_command*)(header+1);
	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			add_output(sym->nsyms, (void*)adr + sym->symoff, (void*)adr + sym->stroff, env);
		}
		lc = (void*)lc + lc->cmdsize;
	}

	order_cmds(env);
	print_cmds(env->list);
}
