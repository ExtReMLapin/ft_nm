/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 09:47:50 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/23 09:33:24 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

/*
** this project sucks, dont ask me to do things correctly
*/

static char			secto(t_lsection *sec, unsigned int n_sect)
{
	t_section		*tmp;

	tmp = sec->first;
	while (tmp)
	{
		if (tmp->nb == n_sect)
		{
			if (!strcmp(tmp->name, SECT_DATA))
				return ('D');
			else if (!strcmp(tmp->name, SECT_BSS))
				return ('B');
			else if (!strcmp(tmp->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		tmp = tmp->next;
	}
	return ('S');
}

char				typing(uint32_t type, uint32_t n_sect,
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

static void			nm(char *ptr, char *end, char *name)
{
	t_env	*env;

	env = make_env(ptr, end, name);
	clearsections(env);
	clearlist(env);
}

int					handlefile(char *filename)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(filename, O_RDONLY)) < 0)
		failmessage("Could not open file\n");
	if (fstat(fd, &buf) < 0)
	{
		write(1, "Could not access file informations, file on fstat().", 52);
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ |
		PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		write(1, "Could not map file to ram.", 26);
		return (EXIT_FAILURE);
	}
	close(fd);
	nm(ptr, ptr + buf.st_size, filename);
	if (munmap(ptr, buf.st_size) < 0)
	{
		write(1, "unmmap fail", 11);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int					main(int ac, char **av)
{
	int i;

	if (ac == 1)
	{
		handlefile("./a.out");
		return (EXIT_SUCCESS);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			if (ac > 2)
			{
				write(1, "\n", 1);
				write(1, av[i], strlen(av[i]));
				write(1, ":\n", 3);
			}
			if (handlefile(av[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
