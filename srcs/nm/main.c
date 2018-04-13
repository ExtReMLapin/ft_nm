/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 09:47:50 by pfichepo          #+#    #+#             */
/*   Updated: 2018/04/12 16:39:53 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

/*
** this project sucks, dont ask me to do things correctly
*/
#include <stdio.h>

static bool				nm(char *ptr, char *end, char *name, int reverse)
{
	t_env		*env;

	if (reverse > 1 && !((*(uint32_t*)ptr == FAT_CIGAM ||
		*(uint32_t*)ptr == FAT_MAGIC)))
	{
		ft_putchar('\n');
		ft_putstr(name);
		ft_putstr(":\n");
	}
	if ((env = make_env(ptr, end, name, reverse == 1)) == NULL)
		return (false);
	clearsections(env);
	clearlist(env);
	free(env);
	return (true);
}

static bool				printerror(int type, char **av, char *filename)
{
	ft_putstr(av[0]);
	ft_putstr(": ");
	ft_putstr(filename);
	if (type == 1)
		ft_putstr(": No such file or directory.");
	else if (type == 2)
		ft_putstr(" The file was not recognized as a valid object file\n");
	else if (type == 3)
		ft_putstr(": Is a directory.");
	else if (type == 4)
		ft_putstr(": No such file or directory/Permission denied.");
	failmessage("\n");
	return (false);
}

static bool				handlefile(char *filename, char **av, bool r, bool pn)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if (filename[0] == '-')
		return (false);
	fd = open(filename, O_RDONLY);
	fstat(fd, &buf);
	if (S_ISDIR(buf.st_mode))
		return (printerror(3, av, filename));
	if ((buf.st_mode & S_IRUSR) == 0)
		return (printerror(4, av, filename));
	if (fd < 0)
		return (printerror(1, av, filename));
	if ((ptr = mmap(0, buf.st_size, PROT_READ |
		PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		failmessage("Could not map file to ram.\n");
		close(fd);
		return (false);
	}
	close(fd);
	if (nm(ptr, ptr + buf.st_size, filename, (int)r + (int)(pn) * 2) == 0)
		return (printerror(2, av, filename));
	return (munmap(ptr, buf.st_size) < 0);
}

int						main(int ac, char **av)
{
	int		i;
	bool	reverse;

	reverse = search_reverse(ac, av);
	if ((ac - (int)reverse) == 1)
	{
		handlefile("./a.out", av, reverse, false);
		return (EXIT_SUCCESS);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			if ((ac - (int)reverse) > 2 && av[i][0] != '-')
				handlefile(av[i++], av, reverse, true);
			else
				handlefile(av[i++], av, reverse, false);
		}
	}
	return (EXIT_SUCCESS);
}

char					*ft_strchr(const char *s, int c)
{
	char a;
	char *ptr;

	ptr = NULL;
	a = (char)(c);
	while (s && (*s != a) && (*s != '\0'))
		s++;
	if (s && (a != '\0') && (*s == '\0'))
		return (NULL);
	else
	{
		ptr = (char *)(s);
		return (ptr);
	}
}
