/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:23 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/01 11:57:39 by pfichepo         ###   ########.fr       */
/*                                                                             */
/* ************************************************************************** */

#include <nm.h> 

static void	handle_fat32(t_env *env, bool swap)
{

	struct fat_header	*header;
	struct fat_arch 	*arch;

	header = (struct fat_header*)env->ptr;	
	arch = (struct fat_arch*)(header+1);

	int i = 0;
	if (swap)
		header->nfat_arch = swap_uint32(header->nfat_arch);
	while (++i <= header->nfat_arch)
	{
		if (swap)
		{
			arch->cputype = (arch->cputype);
			arch->cpusubtype = swap_uint32(arch->cpusubtype);
			arch->offset = swap_uint32(arch->offset);
			arch->size = swap_uint32(arch->size);
			arch->align = swap_uint32(arch->align);
		}
		printf("CPUTYPE %i  CPU SUBTYPE %i  OFFSET %i SIZE %i ALIGN %i\n", arch->cputype, arch->cpusubtype, arch->offset, arch->size, arch->align);

		arch = (void*)arch + sizeof(struct fat_arch);
	}

	exit(0);
}

void handle_fat(t_env *env, bool swap)
{

	struct fat_header	*header;
	struct fat_arch 	*arch;

	header = (struct fat_header*)env->ptr;
	if ((void*)header > (void*)env->end)
		failmessage("Fail header");
	printf(" is64 %i isswap %i\n", env->is64bit,  env->isswap);

	if (!env->is64bit)
		handle_fat32(env, swap);


	exit(0);
}