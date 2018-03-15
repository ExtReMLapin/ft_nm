/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 09:41:11 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/15 10:52:23 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>
#include <ar.h>


bool		check_ar_header(char *ptr)
{
	int i ;

	i = 0;

	while (i++ < SARMAG-1)
	{
		if (ARMAG[i] != ptr[i])
			return (false);
	}
	return (true);
}


static uint32_t	ar_size(char const *name)
{
	char *size;

	size = strchr(name, '/');
	return (atoi(size + 1));
}

static void		read_ranlib(char const *file, char *end, uint32_t nbr, t_env *env)
{
	struct ar_hdr	*ar;
	void			*obj;
	struct ranlib	*ranlib;
	uint32_t		i;

	i = 0;
	ar = (void*)file + SARMAG;
	ranlib = (void*)ar + sizeof(struct ar_hdr) + ar_size(ar->ar_name) + 4;
	while (i < nbr)
	{
		ar = (void*)file + ranlib[i].ran_off;
		obj = (void*)ar + sizeof(struct ar_hdr) + ar_size(ar->ar_name);
		printf("\n%s(%s):\n", env->file_name, ar->ar_name + sizeof(struct ar_hdr));
		nm2(env, (char*)obj, end);
		i++;
	}
}

void				handle_ar(char const *file, char *max, t_env *env)
{
	struct ar_hdr	*ar;
	int				nobj;

	ar = (void *)file + SARMAG;
	nobj = *((int *)((void*)ar + sizeof(struct ar_hdr) + ar_size(ar->ar_name)));
	nobj = nobj / sizeof(struct ranlib);
	read_ranlib(file, max, nobj, env);
}