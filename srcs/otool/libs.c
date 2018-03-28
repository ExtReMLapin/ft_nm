/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 17:19:29 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

struct fat_arch_64	*ffcpu(struct fat_arch_64 *a, cpu_type_t cpu, uint32_t n)
{
	struct fat_arch_64 *ret;

	ret = NULL;
	while (n--)
	{
		if (a->cputype == cpu || (cpu_type_t)swap_uint32(a->cputype) == cpu)
			return (a);
		a = (void*)a + sizeof(struct fat_arch_64);
	}
	return (ret);
}
