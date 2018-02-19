/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 09:47:50 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/19 12:15:08 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int						misc_is_macho_file(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM
		|| magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}


void print_output64(int nsyms, int symoff, int stroff, char* ptr)
{
	int i;
	char *stringtable;
	struct nlist_64 *array;

	array = (void*)ptr + symoff;
	stringtable = (void*)ptr + stroff;

	for (i = 0; i < nsyms; ++i)
	{
		printf("%s\n", stringtable + array[i].n_un.n_strx);
		printf("%i\n",  array[i].n_value);
	}

}


void	handle_64(char *ptr)
{
	int 	ncmds;
	struct	mach_header_64 *header;
	struct  load_command *lc;
	int i;
	struct symtab_command *sym;

	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = (void*)ptr + sizeof(*header);
	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *) lc;
			print_output64(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void*)lc + lc->cmdsize;

	}

}


void nm(char *ptr)
{
	int magic_number;

	magic_number = *(int*)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_MAGIC)
	{
		printf("%s\n", "nope");
	}
	else
		printf("%s\n", "could not find correct magic number");

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
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("%s\n", "mmap fail");
		return (EXIT_FAILURE);
	}
	close(fd);
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		printf("%s\n", "unmmap fail");
		return (EXIT_FAILURE);
	}
	return	(EXIT_SUCCESS);
}