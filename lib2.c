/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/05 15:46:12 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

size_t countspacesbeforehex(uint64_t hex)
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


void	print_hex(uint64_t hex, bool first, bool is64)
{
	char 	hex_chars[16];
	char c;
	int i;

	if (first)
	{
		i = (8 + ((int)is64*8)) - countspacesbeforehex(hex);
		if (hex == 0x0)
			c = ' ';
		else
			c = '0';
		while (i--)
			putchar(c);
		if (hex == 0x0)
			return;
	}
	memcpy(hex_chars, "0123456789abcdef", sizeof(char) * 16);
	if (hex > 15)
	{
		print_hex(hex / 16, false, is64);
		print_hex(hex % 16, false, is64);
	}
	else
		putchar(hex_chars[hex]);
}