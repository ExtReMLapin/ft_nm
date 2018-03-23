/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:07 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/23 11:42:23 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>



static int	print_section(struct section_64 *s, char const *h)
{
	uint64_t	i;
	uint64_t	j;
	uint64_t	addr;
	uint64_t	off;

	i = 0;
	addr = s->addr;
	off = s->offset;
	while (i < s->size)
	{
		j = 0;
		printf("%0.16llx\t", addr);
		while (j < 16 && i + j < s->size)
		{
			printf("%.2hhx ", *(h + off));
			off++;
			j++;
		}
		printf("\n");
		i += j;
		addr += j;
	}
	return (1);
}

static int	lc_seg_64(struct segment_command_64 *sc, char const *h)
{
	uint64_t			i;
	struct section_64	*s;
	char				*str;

	i = 0;
	s = (struct section_64*)(sc + 1);
	str = SECT_TEXT;
	while (i < sc->nsects)
	{
		if (strequ(s[i].segname, SEG_TEXT)
			&& strequ(s[i].sectname, SECT_TEXT))
		{
			printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			print_section(s + i, h);
		}
		i++;
	}
	return (1);
}

void		handle_64(t_env *env, char *adr, char *max, bool swap)
{
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						i;
	struct symtab_command_64	*sym;

	header = (struct mach_header_64*)adr;
	segfaultcheck((char*)header, max, AT);
	ncmds = (swap) ? swap_uint32(header->ncmds) : header->ncmds;
	lc = (struct load_command*)(header + 1);
	i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			sym = (struct symtab_command_64 *)lc;
			lc_seg_64((struct segment_command_64*)lc, adr);
			
		}
		lc = (void*)lc + lc->cmdsize;
	}

}
