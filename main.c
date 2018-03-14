/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 09:47:50 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/14 10:15:45 by pfichepo         ###   ########.fr       */
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

char				typing(uint32_t type, uint32_t n_sect, t_lsection *sec, int addr)
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




void nm(char *ptr, char* end)
{
	t_env *env;

	env = make_env(ptr, end);
}

int main (int ac, char ** av)
{
	int				fd;
	char			*ptr;
	struct stat 	buf;

	if (ac != 2)
	{	
		printf("%s\n", "fail narg");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		printf("%s\n", "fail on open");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		printf("%s\n", "fstat");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("%s\n", "mmap fail");
		return (EXIT_FAILURE);
	}
	close(fd);
	nm(ptr, ptr + buf.st_size);
	if (munmap(ptr, buf.st_size) < 0)
	{
		printf("%s\n", "unmmap fail");
		return (EXIT_FAILURE);
	}
	return	(EXIT_SUCCESS);
}
