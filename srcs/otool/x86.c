/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x86.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:17 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/23 10:52:21 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>



void		handle_32(t_env *env, char *adr, char *max, bool swap)
{
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	int						i;
	struct symtab_command	*sym;

	header = (struct mach_header*)adr;
	segfaultcheck((char*)header, max, AT);
	ncmds = (swap) ? swap_uint32(header->ncmds) : header->ncmds;
	lc = (struct load_command*)(header + 1);
	i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;

		}
		lc = (void*)lc + lc->cmdsize;
	}

}
