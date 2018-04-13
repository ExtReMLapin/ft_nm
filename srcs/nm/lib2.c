/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:28:35 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/29 09:42:03 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

size_t		countcharhex(uint64_t hex)
{
	int i;

	i = (hex > 0x0);
	if (i == 0)
		return (0);
	while (hex > 15)
	{
		hex = hex / 16;
		i++;
	}
	return (i);
}

void		print_hex(uint64_t hex, bool first, int how_many_chars, bool blank)
{
	char	hex_chars[16];
	char	c;
	int		i;

	if (first)
	{
		i = how_many_chars - countcharhex(hex);
		if (blank)
			c = ' ';
		else
			c = '0';
		while (i--)
			ft_putchar(c);
		if (hex == 0x0)
			return ;
	}
	ft_memcpy(hex_chars, "0123456789abcdef", sizeof(char) * 16);
	if (hex > 15)
	{
		print_hex(hex / 16, false, 0, blank);
		print_hex(hex % 16, false, 0, blank);
	}
	else
		ft_putchar(hex_chars[hex]);
}

static char	secto(t_lsection *sec, unsigned int n_sect)
{
	t_section		*tmp;

	tmp = sec->first;
	while (tmp)
	{
		if (tmp->nb == n_sect)
		{
			if (!ft_strcmp(tmp->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		tmp = tmp->next;
	}
	return ('S');
}

char		typing(uint32_t type, uint32_t n_sect,
	t_lsection *sec, int addr)
{
	char			ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_TYPE) == N_SECT)
		ret = secto(sec, n_sect);
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

bool		search_reverse(int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-r") == 0)
			return (true);
		i++;
	}
	return (false);
}
