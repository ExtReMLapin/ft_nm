/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 09:47:50 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 12:33:36 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

/*
** this project sucks, dont ask me to do things correctly
*/

static void				otool(char *ptr, char *end, char *name)
{
	t_env	*env;

	if ((env = make_env(ptr, end, name)) == NULL)
	{
		ft_putstr("File not recognized");
		return ;
	}
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

bool					handlefile(char *filename, char **av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

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
		failmessage("Could not map file to ram.");
		close(fd);
		return (false);
	}
	close(fd);
	otool(ptr, ptr + buf.st_size, filename);
	if (munmap(ptr, buf.st_size) < 0)
		failmessage("unmmap fail");
	return (true);
}

int						main(int ac, char **av)
{
	int i;

	if (ac == 1)
	{
		handlefile("./a.out", av);
		return (EXIT_SUCCESS);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			handlefile(av[i], av);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
