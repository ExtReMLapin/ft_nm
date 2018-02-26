/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/26 10:11:53 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		failmessage(char *message)
{
	printf("%s\n",message);
	exit(EXIT_FAILURE);
}




void 	swapcmds(t_cmd *a, t_cmd *b)
{
	uint64_t				adr;
	char					symbol;
	char					*name;

	adr = a->adr;
	symbol = a->symbol;
	name = a->name;


	a->adr = b->adr;
	a->symbol = b->symbol;
	a->name = b->name;

	b->adr = adr;
	b->symbol = symbol;
	b->name = name;
}

/*
** Is in the ascii table, a > b ?
*/

bool isstrbigger(char *a, char *b)
{
	int i = 0;

	if (!b || !a)
		failmessage("Attempt to cmp two string is bigger but one is invalid");
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

t_cmd *has_fucked_up_order_cmds(t_env *env)
{
	t_cmd *cmds;

	cmds = env->list;
	while (cmds->next)
	{
		if (isstrbigger(cmds->name, cmds->next->name))
			return (cmds);
		cmds = cmds->next;
	}
	return (NULL);
}

void 	order_cmds(t_env *env)
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


void Bite(void)
{
	return;
}


void bite(void)
{
	return;
}








































