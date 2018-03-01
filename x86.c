/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x86.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:17 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/01 10:12:25 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void add_output(int nsyms, int symoff, int stroff, t_env* env)
{
	int i;
	char *stringtable;
	struct nlist *array;
	t_cmd *cmd;

	array = (void*)env->ptr + symoff;
	stringtable = (void*)env->ptr + stroff;
	cmd = NULL;
	for (i = 0; i < nsyms; ++i)
	{
		mlccmd(env, array[i].n_value, get_symbol(array[i].n_type), stringtable + array[i].n_un.n_strx);
	}
}


void	handle_32(t_env *env)
{
	int 	ncmds;
	struct	mach_header *header;
	struct  load_command *lc;
	int i;
	struct symtab_command *sym;

	header = (struct mach_header*)env->ptr;
	if ((void*)header > (void*)env->end)
		failmessage("Fail header");
	ncmds = header->ncmds;
	lc = (void*)env->ptr + sizeof(struct	mach_header);
	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			add_output(sym->nsyms, sym->symoff, sym->stroff, env);
			break;
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

void	handle_32r(t_env *env)
{
	handle_64r(env);
}