/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:07 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 12:16:52 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static uint64_t	nique_la_norme(uint64_t j, uint64_t off, char *h, t_env *env)
{
	uint64_t col;

	col = *(h + off) & 0xff;
	if (COLORS == 1)
	{
		if (col == 0)
			ft_putstr("\e[2m");
		else if (col == 0xff)
			ft_putstr("\e[100m");
	}
	print_hex(col, true, 2, false);
	if (COLORS == 1)
		ft_putstr("\e[0m");
	if (j % 4 == 3 || !env->in_ppc)
		ft_putchar(' ');
	return (++j);
}

static void		print_section(struct section_64 *s, char *h, bool w, t_env *e)
{
	uint64_t	i;
	uint64_t	j;
	uint64_t	addr;
	uint64_t	off;

	i = 0;
	addr = (w) ? swap_uint32(s->addr) : s->addr;
	off = (w) ? swap_uint32(s->offset) : s->offset;
	s->size = (w) ? swap_uint32(s->size) : s->size;
	while (i < s->size)
	{
		j = 0;
		if (COLORS == 1)
			ft_putstr("\e[1m");
		print_hex(addr, true, 16, false);
		if (COLORS == 1)
			ft_putstr("\e[0m");
		ft_putchar('\t');
		while (j < 16 && i + j < s->size)
			j = nique_la_norme(j, off++, h, e);
		ft_putchar('\n');
		i += j;
		addr += j;
	}
}

static int		lc1(struct segment_command_64 *sc, char *h, bool z, t_env *e)
{
	uint64_t			i;
	struct section_64	*s;
	char				*str;

	i = 0;
	s = (struct section_64*)(sc + 1);
	str = SECT_TEXT;
	sc->nsects = (z) ? swap_uint32(sc->nsects) : sc->nsects;
	while (i < sc->nsects)
	{
		if (strequ(s[i].segname, SEG_TEXT) && strequ(s[i].sectname, SECT_TEXT))
		{
			ft_putstr("Contents of (");
			ft_putstr(SEG_TEXT);
			ft_putchar(',');
			ft_putstr(SECT_TEXT);
			ft_putstr(") section\n");
			print_section(s + i, h, z, e);
		}
		i++;
	}
	return (1);
}

void			handle_64(char *adr, char *max, bool swap, t_env *env)
{
	int							ncmds;
	struct mach_header_64		*header;
	struct load_command			*lc;
	int							i;
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
			lc1((struct segment_command_64*)lc, adr, swap, env);
		}
		lc = (void*)lc + lc->cmdsize;
	}
}
