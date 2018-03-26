/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:20:20 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/26 11:27:35 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

void			otool2(t_env *env, char *ptr, char *max)
{
	uint32_t head;

	head = *(uint32_t*)ptr;

	if (head == MH_MAGIC_64)
		handle_64(ptr, max, false || env->in_ppc);
	else if (head == MH_CIGAM_64)
		handle_64(ptr, max, true);
	else if (head == MH_MAGIC)
		handle_32(ptr, max, false || env->in_ppc);
	else if (head == MH_CIGAM)
		handle_32(ptr, max, true);
	else
		failmessage("ohohoh, pas normal\n");
}

void			segfaultcheck(char *ptr, char *end, char *mess)
{
	if (ptr > end)
	{
		write(1, "Antisegfault at ", 16);
		write(1, mess, strlen(mess));
		failmessage(".\n");
	}
}

bool			check_ar_header(char *ptr)
{
	int i;

	i = 0;
	while (i++ < SARMAG - 1)
	{
		if (ARMAG[i] != ptr[i])
			return (false);
	}
	return (true);
}

void			handle_ar(char const *file, char *max, t_env *env)
{
	struct ar_hdr	*ar;
	int				nobj;

	ar = (void *)file + SARMAG;
	nobj = *((int *)((void*)ar + sizeof(struct ar_hdr) + ar_size(ar->ar_name)));
	nobj = nobj / sizeof(struct ranlib);
	read_ranlib(file, max, nobj, env);
}

uint32_t		ar_size(char const *name)
{
	char *size;

	size = strchr(name, '/');
	return (atoi(size + 1));
}
