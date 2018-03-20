/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/20 12:34:12 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

/*
** Is in the ascii table, a > b ?
*/

bool		isstrbigger(char *a, char *b)
{
	int i;

	i = 0;
	if (!b || !a)
		failmessage("Attempt to cmp two string is bigger but one is invalid");
	if (strcmp(a, b) == 0)
		return (false);
	while (a[i] && b[i])
	{
		if (a[i] > b[i])
			return (true);
		if (a[i] < b[i])
			return (false);
		i++;
	}
	if (b[i] == '\0')
		return (true);
	else
		return (false);
}

/*
** Fucking hell in-efficent code right after it, NSFW
*/

t_cmd 		*has_fucked_up_order_cmds(t_env *env)
{
	t_cmd *cmds;

	cmds = env->list;
	if (cmds == NULL)
		failmessage("no cmds found");
	int i = 0;
	while (cmds->next)
	{
		if (isstrbigger(cmds->name, cmds->next->name))
			return (cmds);
		cmds = cmds->next;
		i++;
	}
	return (NULL);
}

void 		order_cmds(t_env *env)
{
	t_cmd	*cmds;

	while(true)
	{
		cmds = has_fucked_up_order_cmds(env);
		if (cmds)
			swapcmds(cmds, cmds->next);
		else
			break;
	}
}

void		print_cmds(t_cmd *cmd, int n)
{
	t_cmd *cmds;

	cmds = cmd;
	while (cmds)
	{
		if (cmds->symbol != 'z' && cmds->symbol != 'Z')
		{
			print_hex(cmds->adr, true, n, cmds->symbol == 'U');
			//printf(" %c %s\n", cmds->symbol, cmds->name);
			write(1, " ", 1);
			write(1, &(cmds->symbol), 1);
			write(1, " ", 1);
			write(1, cmds->name, strlen(cmds->name));
			write(1, "\n", 1);
		}
		cmds = cmds->next;
	}
}
