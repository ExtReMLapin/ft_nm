/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/08 09:41:46 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>


int how_many_chars(t_env *env)
{
	if (env->is64bit || env->isfattype)
		return (16);
	return (8);
}


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


void	print_hex(uint64_t hex, bool first, t_env *env)
{
	char 	hex_chars[16];
	char c;
	int i;

	if (first)
	{
		i = how_many_chars(env) - countspacesbeforehex(hex);
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
		print_hex(hex / 16, false, env);
		print_hex(hex % 16, false, env);
	}
	else
		putchar(hex_chars[hex]);
}