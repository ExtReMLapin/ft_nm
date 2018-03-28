/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 10:44:03 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

/*
** Is in the ascii table, a > b ?
*/

int					isstrbigger(char *a, char *b)
{
	int	i;

	i = 0;
	if (!b || !a)
		failmessage("Attempt to cmp two string is bigger but one is invalid\n");
	if (strcmp(a, b) == 0)
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
		strbigger = isstrbigger(cmds->name, cmds->next->name);
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
			write(1, " ", 1);
			write(1, &(cmds->symbol), 1);
			write(1, " ", 1);
			write(1, cmds->name, strlen(cmds->name));
			write(1, "\n", 1);
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
