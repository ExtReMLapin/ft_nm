/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfat2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 09:36:17 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/20 10:32:54 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

char*			get_cputype(cpu_type_t	cputype)
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
	else
		return ("?");
}

static bool		hascpu(cpu_type_t cpu, struct fat_arch* arch, uint32_t n)
{
	while (n--)
	{
		if (arch->cputype == cpu || (cpu_type_t)swap_uint32(arch->cputype) == cpu)
			return (true);
		arch = (void*)arch + sizeof(struct fat_arch);
	}
	return (false);
}

/*
** Could make a get_cputype in bool to get faster result but im lazy
*/

bool			shouldprintcpu(cpu_type_t cpu, struct fat_arch* arch, uint32_t n)
{
	if (get_cputype(cpu)[0] == '?')
		return (false); 
	if (cpu == CPU_TYPE_X86 || cpu == CPU_TYPE_I386)
		return (!hascpu(CPU_TYPE_X86_64, arch, n));
	return (true);
}

unsigned int	how_many_cpu(struct fat_arch* arch, uint32_t n)
{
	bool has_i386;
	bool has_x86_x64;
	unsigned int count;

	has_i386 = false;
	has_x86_x64 = false;
	count = 0;
	while (n--)
	{
		if (arch->cputype == CPU_TYPE_X86 || arch->cputype == CPU_TYPE_I386 ||
			swap_uint32(arch->cputype) == CPU_TYPE_X86 || swap_uint32(arch->cputype) == CPU_TYPE_I386 )
		{
			has_i386 = true;
		}
		if (arch->cputype == CPU_TYPE_X86_64 || swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			has_x86_x64 = true;
		if (get_cputype(arch->cputype)[0] != '?' || get_cputype(swap_uint32(arch->cputype))[0] != '?')
			count++;
		arch = (void*)arch + sizeof(struct fat_arch);
	}
	if (has_x86_x64 && has_i386)
		count--;
	return (count);
}