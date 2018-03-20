/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 09:41:11 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/20 12:41:34 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

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

static uint32_t	ar_size(char const *name)
{
	char *size;

	size = strchr(name, '/');
	return (atoi(size + 1));
}

static bool		isartablesorted(uint32_t *table, uint32_t nbr)
{
	uint32_t i;
	uint32_t cache;

	i = 0;
	while (i < nbr)
	{
		if (i + 1 == nbr)
			break ;
		if (table[i] > table[i + 1])
		{
			cache = table[i];
			table[i] = table[i + 1];
			table[i + 1] = cache;
			return (false);
		}
		i++;
	}
	return (true);
}

static uint32_t	*filtertable(uint32_t nbr, struct ranlib	*ranlib)
{
	uint32_t	i;
	uint32_t	*artable;

	if ((artable = (uint32_t*)malloc(sizeof(uint32_t) * nbr)) == NULL)
		failmessage("FailMalloc");
	i = 0;
	while (i < nbr)
	{
		artable[i] = ranlib[i].ran_off;
		i++;
	}
	while (true)
	{
		if (isartablesorted(artable, nbr) == true)
			break ;
	}
	return (artable);
}

static void printext(char* file_name, char* ar_name)
{
	write(1, "\n", 1);
	write(1, file_name , strlen(file_name));
	write(1, "(", 1);
	write(1, ar_name, strlen(ar_name));
	write(1, "):\n", 3);

}

static void		read_ranlib(char const *file, char *end, uint32_t nbr, t_env *env)
{
	struct ar_hdr	*ar;
	void			*obj;
	struct ranlib	*ranlib;
	uint32_t		i;
	uint32_t *artable;

	ar = (void*)file + SARMAG;
	ranlib = (void*)ar + sizeof(struct ar_hdr) + ar_size(ar->ar_name) + 4;
	artable = filtertable(nbr, ranlib);
	i = 0;
	while (i < nbr)
	{
		while (i != 0 && artable[i] == artable[i - 1])
			i++;
		if (i >= nbr)
			break ;
		ar = (void*)file + artable[i];
		obj = (void*)ar + sizeof(struct ar_hdr) + ar_size(ar->ar_name);
		printext(env->file_name, ar->ar_name + sizeof(struct ar_hdr));
		nm2(env, (char*)obj, end);
		i++;
	}
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
