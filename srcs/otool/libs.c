/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 11:19:04 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

/*
** Is in the ascii table, a > b ?
*/

bool				isstrbigger(char *a, char *b)
{
	int	i;

	i = 0;
	if (!b || !a)
		failmessage("Attempt to cmp two string is bigger but one is invalid\n");
	if (ft_strcmp(a, b) == 0)
		return (false);
	while (a[i] && b[i])
	{
		if (a[i] > b[i])
			return (true);
		if (a[i] < b[i])
			return (false);
		i++;
	}
	if (b[i] == '\0')
		return (true);
	else
		return (false);
}

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
