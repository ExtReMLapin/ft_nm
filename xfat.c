/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:23 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/19 10:17:45 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <nm.h>



static char*		get_cputype(cpu_type_t cputype)
{
	if (cputype == CPU_TYPE_VAX)
		return ("vax");
	else if (cputype == CPU_TYPE_MC680x0)
		return ("mc680");
	else if (cputype == CPU_TYPE_X86 || cputype == CPU_TYPE_I386)
		return ("i386");
	else if (cputype == CPU_TYPE_X86_64)
		return ("x86_64");
	else if (cputype == CPU_TYPE_MC98000)
		return ("mc98000");
	else if (cputype == CPU_TYPE_HPPA)
		return ("hppa");
	else if (cputype == CPU_TYPE_ARM)
		return ("arm");
	else if (cputype == CPU_TYPE_MC88000)
		return ("mc880000");
	else if (cputype == CPU_TYPE_SPARC)
		return ("sparc");
	else if (cputype == CPU_TYPE_I860)
		return ("i860");
	else if (cputype == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (cputype == CPU_TYPE_POWERPC64)
		return ("ppc64");
	return ("???");
}



static bool validcpu(cpu_type_t cputype)
{
	if (cputype == CPU_TYPE_X86_64 || cputype == CPU_TYPE_POWERPC || cputype == CPU_TYPE_ARM64)
		return (true);
	return (false);

}

static int toprint_arch(struct fat_arch *arch, bool swap, uint32_t n)
{
	int			i;
	cpu_type_t	cputype;

	i = 0;
	while (n--)
	{
		cputype = (swap) ? swap_uint32(arch->cputype) : arch->cputype;

		if (validcpu(cputype))
			i++;
		arch = (void*)arch + sizeof(struct fat_arch);
	}
	return (i);
}

static void	handle_fat32(t_env *env, bool swap)
{
	struct fat_header	*header;
	struct fat_arch 	*arch;
	struct mach_header	*header2;
	int toprint;


	header = (struct fat_header*)env->ptr;	
	arch = (struct fat_arch*)(header+1);
	header->nfat_arch = (swap) ? swap_uint32(header->nfat_arch) : header->nfat_arch;
	toprint = toprint_arch(arch, swap,header->nfat_arch );
	while (header->nfat_arch--)
	{
		arch->cputype = (swap) ? swap_uint32(arch->cputype) : arch->cputype;
		arch->cpusubtype = (swap) ? swap_uint32(arch->cpusubtype) : arch->cpusubtype;
		arch->offset = (swap) ? swap_uint32(arch->offset) : arch->offset;
		arch->size = (swap) ? swap_uint32(arch->size) : arch->size;
		arch->align = (swap) ? swap_uint32(arch->align) : arch->align;
		header2 = (void*)env->ptr + arch->offset;
		if (validcpu(arch->cputype))
		{
			if (toprint > 1)
			{
				printf("%s (for architecture %s):\n", env->file_name, get_cputype(arch->cputype));
			}
			nm2(env, (char*)header2, (char*)((void*)header2 + arch->size));
		}
		printf("cputype = 0x%08x cpusubtype = 0x%08x offset = %i size = %i align = %i \n", arch->cputype, arch->cpusubtype, arch->offset, arch->size, arch->align);


		arch = (void*)arch + sizeof(struct fat_arch);
	}	
}

static void	handle_fat64(t_env *env, bool swap)
{
	struct fat_header	*header;
	struct fat_arch_64 	*arch;
	struct mach_header_64	*header2;

	header = (struct fat_header*)env->ptr;	
	arch = (struct fat_arch_64*)(header+1);
	if (swap)
		header->nfat_arch = swap_uint64(header->nfat_arch);
	while (header->nfat_arch--)
	{
		arch->cputype = (swap) ? swap_uint64(arch->cputype) : arch->cputype;
		arch->cpusubtype = (swap) ? swap_uint64(arch->cpusubtype) : arch->cpusubtype;
		arch->offset = (swap) ? swap_uint64(arch->offset) : arch->offset;
		arch->size = (swap) ? swap_uint64(arch->size) : arch->size;
		arch->align = (swap) ? swap_uint64(arch->align) : arch->align;
		header2 = (void*)env->ptr + arch->offset;
		if (arch->cputype == CPU_TYPE_X86_64)
		{
			nm2(env, (char*)header2, (char*)((void*)header2 + arch->size));
			break;
		}
		arch = (void*)arch + sizeof(struct fat_arch_64);
	}	
}

void handle_fat(t_env *env, bool swap)
{
	struct fat_header	*header;


	printf("%s\n", "fathandle");
	header = (struct fat_header*)env->ptr;
	if ((void*)header > (void*)env->end)
		failmessage("Fail header");
	if (!env->is64bit)
		handle_fat32(env, swap);
	else
		handle_fat64(env, swap);
}