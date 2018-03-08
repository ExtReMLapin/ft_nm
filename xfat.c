/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:23 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/08 12:14:53 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <nm.h> 


static void	handle_fat32(t_env *env, bool swap)
{
	struct fat_header	*header;
	struct fat_arch 	*arch;
	struct mach_header	*header2;

	header = (struct fat_header*)env->ptr;	
	arch = (struct fat_arch*)(header+1);
	if (swap)
		header->nfat_arch = swap_uint32(header->nfat_arch);
	while (header->nfat_arch--)
	{
		arch->cputype = (swap) ? swap_uint32(arch->cputype) : arch->cputype;
		arch->cpusubtype = (swap) ? swap_uint32(arch->cpusubtype) : arch->cpusubtype;
		arch->offset = (swap) ? swap_uint32(arch->offset) : arch->offset;
		arch->size = (swap) ? swap_uint32(arch->size) : arch->size;
		arch->align = (swap) ? swap_uint32(arch->align) : arch->align;
		header2 = (void*)env->ptr + arch->offset;
		if (arch->cputype == CPU_TYPE_X86_64)
		{
			nm2(env, (char*)header2, (char*)((void*)header2 + arch->size));
			break;
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
	if (!env->is64bit)
		handle_fat32(env, swap);
}