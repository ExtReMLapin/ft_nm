/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:07 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/27 10:34:21 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static uint64_t nique_la_norme(uint64_t j, uint64_t off, char* h, t_env *env)
{
	print_hex(*(h + off) & 0xff, true, 2, false);
	if (j%4 == 3 || !env->in_ppc)
		ft_putchar(' ');
	return (++j);
}

static int	print_section(struct section_64 *s, char *h, bool swap, t_env *env)
{
	uint64_t	i;
	uint64_t	j;
	uint64_t	addr;
	uint64_t	off;

	i = 0;
	addr = (swap) ? swap_uint32(s->addr): s->addr;
	off = (swap) ? swap_uint32(s->offset) : s->offset;
	s->size = (swap) ? swap_uint32(s->size) : s->size;
	while (i < s->size)
	{
		j = 0;
		print_hex(addr, true, 16, false);
		ft_putchar('\t');
		while (j < 16 && i + j < s->size)
		{
			j = nique_la_norme(j, off, h, env);
			off++;	
		}
		ft_putchar('\n');
		i += j;
		addr += j;
	}
	return (1);
}

static int	lc_seg_64(struct segment_command_64 *sc, char *h, bool swap, t_env *env)
{
	uint64_t			i;
	struct section_64	*s;
	char				*str;

	i = 0;
	s = (struct section_64*)(sc + 1);
	str = SECT_TEXT;
	sc->nsects = (swap) ? swap_uint32(sc->nsects) : sc->nsects;
	while (i < sc->nsects)
	{
		if (strequ(s[i].segname, SEG_TEXT) && strequ(s[i].sectname, SECT_TEXT))
		{
			ft_putstr("Contents of (");
			ft_putstr(SEG_TEXT);
			ft_putchar(',');
			ft_putstr(SECT_TEXT);
			ft_putstr(") section\n");
			print_section(s + i, h, swap, env);
		}
		i++;
	}
	return (1);
}

void		handle_64(char *adr, char *max, bool swap, t_env *env)
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
		lc->cmdsize = (swap) ? swap_uint32(lc->cmdsize) : lc->cmdsize;
		lc->cmd = (swap) ? swap_uint32(lc->cmd) : lc->cmd;
		if (lc->cmd == LC_SEGMENT_64)
		{
			sym = (struct symtab_command_64 *)lc;
			lc_seg_64((struct segment_command_64*)lc, adr, swap, env);
		}
		lc = (void*)lc + lc->cmdsize;
	}

}
