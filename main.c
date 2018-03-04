/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 09:47:50 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/28 10:30:00 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

char get_symbol(uint8_t value)
{
	if (value == 1)
		return ('U');
	if (value == 15)
		return ('T');
	if (value == 14)
		return ('t');
	else
		return ('?');
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
