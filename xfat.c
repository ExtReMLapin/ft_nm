/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:23 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/08 11:22:13 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <nm.h> 

static void add_output(int nsyms, int symoff, int stroff, t_env* env, char* start)
{
	int		i;
	char	*stringtable;
	struct	nlist *array;
	t_cmd	*cmd;

	array = (void*)start + symoff;
	stringtable = (void*)start + stroff;
	cmd = NULL;
	for (i = 0; i < nsyms; ++i)
	{
		if (((void*)&array[i] + sizeof(*array) > (void*)env->end) || (void*)stringtable > (void*)env->end)
			failmessage("Please check file integrity");
		if (get_symbol(array[i].n_type) != '?')
			mlccmd(env, array[i].n_value, get_symbol(array[i].n_type), stringtable + array[i].n_un.n_strx);
	}
}


static void	handle_fat32(t_env *env, bool swap)
{

	struct fat_header	*header;
	struct fat_arch 	*arch;

	

	header = (struct fat_header*)env->ptr;	
	arch = (struct fat_arch*)(header+1);
	if (swap)
		header->nfat_arch = swap_uint32(header->nfat_arch);
	while (header->nfat_arch--)
	{

		
		if (swap)
		{
			arch->cputype = swap_uint32(arch->cputype);
			arch->cpusubtype = swap_uint32(arch->cpusubtype);
			arch->offset = swap_uint32(arch->offset);
			arch->size = swap_uint32(arch->size);
			arch->align = swap_uint32(arch->align);
		}
		struct	mach_header *header2;
		header2 = (void*)env->ptr + arch->offset;
		
		if (arch->cputype == CPU_TYPE_X86_64)
		{
			int 	ncmds;
	
			struct  segment_command *lc;
			int i;
			struct symtab_command *sym;

			
			if ((void*)header2 > (void*)env->end)
				failmessage("Fail header");
			ncmds = header2->ncmds;
			lc = (struct  segment_command*)(header2+1);
			for (i = 0; i < ncmds; ++i)
			{
				printf("%i\n", lc->cmd);
				if (lc->cmd == LC_SYMTAB)
				{
					sym = (struct symtab_command *) lc;
					add_output(sym->nsyms, sym->symoff, sym->stroff, env, (char*)header2);
					
					break;
				}
				
				lc = (void*)lc + lc->cmdsize;
				
			}
		
		}
		arch = (void*)arch + sizeof(struct fat_arch);
	}

	
}

void handle_fat(t_env *env, bool swap)
{

	struct fat_header	*header;

	header = (struct fat_header*)env->ptr;
	if ((void*)header > (void*)env->end)
		failmessage("Fail header");
	//printf(" is64 %i isswap %i\n", env->is64bit,  env->isswap);

	if (!env->is64bit)
		handle_fat32(env, swap);



}