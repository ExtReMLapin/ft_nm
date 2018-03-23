/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:28:35 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/21 11:29:29 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

size_t	countcharhex(uint64_t hex)
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

void	print_hex(uint64_t hex, bool first, int how_many_chars, bool blank)
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
			write(1, &c, 1);
		if (hex == 0x0)
			return ;
	}
	memcpy(hex_chars, "0123456789abcdef", sizeof(char) * 16);
	if (hex > 15)
	{
		print_hex(hex / 16, false, 0, blank);
		print_hex(hex % 16, false, 0, blank);
	}
	else
		write(1, &hex_chars[hex], 1);
}
