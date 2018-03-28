/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 17:31:44 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

/*
** Is in the ascii table, a > b ?
*/

static int			isstrbigger(char *a, char *b)
{
	int	i;

	i = 0;
	if (!b || !a)
		failmessage("Attempt to cmp two string is bigger but one is invalid\n");
	if (ft_strcmp(a, b) == 0)
		return (-1);
	while (a[i] && b[i])
	{
		if (a[i] > b[i])
			return (1);
		if (a[i] < b[i])
			return (0);
		i++;
	}
	if (b[i] == '\0')
		return (1);
	else
		return (0);
}

/*
** Fucking hell in-efficent code right after it, NSFW
*/

t_cmd				*has_fucked_up_order_cmds(t_env *env)
{
	t_cmd	*cmds;
	int		i;
	int		strbigger;

	cmds = env->list;
	if (cmds == NULL)
		failmessage("no cmds found\n");
	i = 0;
	while (cmds->next)
	{
		segfaultcheck(cmds->name, env->end, AT);
		segfaultcheck(cmds->next->name, env->end, AT);
		strbigger = isstrbigger(cmds->name, cmds->next->name) != env->reverse;
		if (strbigger == 1 || (strbigger == -1 && cmds->adr > cmds->next->adr))
			return (cmds);
		cmds = cmds->next;
		i++;
	}
	return (NULL);
}

void				order_cmds(t_env *env)
{
	t_cmd	*cmds;

	while (true)
	{
		cmds = has_fucked_up_order_cmds(env);
		if (cmds)
			swapcmds(cmds, cmds->next);
		else
			break ;
	}
}

void				print_cmds(t_cmd *cmd, int n)
{
	t_cmd	*cmds;

	cmds = cmd;
	while (cmds)
	{
		if (cmds->symbol != 'z' && cmds->symbol != 'Z')
		{
			print_hex(cmds->adr, true, n, cmds->symbol == 'U');
			ft_putchar(' ');
			if (COLORS == 1)
			{
				if (cmds->symbol == 'U')
					ft_putstr("\e[101m");
			}
			ft_putchar(cmds->symbol);
			if (COLORS == 1)
				ft_putstr("\e[0m");
			ft_putchar(' ');
			ft_putstr(cmds->name);
			ft_putchar('\n');
		}
		cmds = cmds->next;
	}
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

/*
** Could make a get_cputype in bool to get faster result but im lazy
*/
