/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfat2_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 09:36:17 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 10:46:59 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static bool	check_var_cpu(cpu_type_t c, bool one, bool current)
{
	if (one)
	{
		if (c == CPU_TYPE_X86 || c == CPU_TYPE_I386 ||
			swap_uint32(c) == CPU_TYPE_X86 || swap_uint32(c) == CPU_TYPE_I386)
		{
			return (true);
		}
		return (current);
	}
	else
	{
		if (c == CPU_TYPE_X86_64 || swap_uint32(c) == CPU_TYPE_X86_64)
			return (true);
		else
			return (current);
	}
}

bool		spcpu64(struct fat_arch_64 *c, struct fat_arch_64 *a, uint32_t n)
{
	if (get_cputype(c->cputype)[0] == '?')
		return (false);
	if (ffcpu(a, c->cputype, n) != c)
		return (false);
	if (c->cputype == CPU_TYPE_X86 || c->cputype == CPU_TYPE_I386)
		return (ffcpu(a, CPU_TYPE_X86_64, n) == NULL);
	return (true);
}

uint32_t	how_many_cpu64(struct fat_arch_64 *a, uint32_t n)
{
	bool			has_i386;
	bool			has_x86_x64;
	unsigned int	count;
	cpu_type_t		c;
	t_pack64		p;

	p.noriginal = n;
	p.original = a;
	has_i386 = false;
	has_x86_x64 = false;
	count = 0;
	while (n--)
	{
		c = a->cputype;
		has_i386 = check_var_cpu(c, true, has_i386);
		has_x86_x64 = check_var_cpu(c, false, has_x86_x64);
		if ((get_cputype(c)[0] != '?' || get_cputype(swap_uint32(c))[0] != '?')
			&& ffcpu(p.original, c, p.noriginal) == a)
		{
			count++;
		}
		a = (void*)a + sizeof(struct fat_arch_64);
	}
	return ((has_x86_x64 && has_i386) ? count - 1 : count);
}
