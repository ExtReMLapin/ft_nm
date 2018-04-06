/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x86.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:17 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 12:16:51 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static uint32_t	nique_la_norme(uint32_t j, uint32_t off, char *h, t_env *env)
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

static void		print_section(struct section *s, char *h, bool w, t_env *e)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	addr;
	uint32_t	off;

	i = 0;
	addr = (w) ? swap_uint32(s->addr) : s->addr;
	off = (w) ? swap_uint32(s->offset) : s->offset;
	s->size = (w) ? swap_uint32(s->size) : s->size;
	while (i < s->size)
	{
		j = 0;
		if (COLORS == 1)
			ft_putstr("\e[1m");
		print_hex(addr, true, 8, false);
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

static int		lc1(struct segment_command *sc, char *h, bool swap, t_env *env)
{
	uint32_t			i;
	struct section		*s;
	char				*str;

	i = 0;
	s = (struct section*)(sc + 1);
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

void			handle_32(char *adr, char *max, bool swap, t_env *env)
{
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	int						i;
	struct symtab_command	*sym;

	header = (struct mach_header*)adr;
	if (segfaultcheck((char*)header, max, AT))
		return ;
	ncmds = (swap) ? swap_uint32(header->ncmds) : header->ncmds;
	lc = (struct load_command*)(header + 1);
	i = 0;
	while (i++ < ncmds)
	{
		lc->cmdsize = (swap) ? swap_uint32(lc->cmdsize) : lc->cmdsize;
		lc->cmd = (swap) ? swap_uint32(lc->cmd) : lc->cmd;
		if (lc->cmd == LC_SEGMENT)
		{
			sym = (struct symtab_command *)lc;
			lc1((struct segment_command*)lc, adr, swap, env);
		}
		lc = (void*)lc + lc->cmdsize;
	}
}
