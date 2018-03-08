/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/08 09:48:10 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>


uint16_t	swap_uint16(uint16_t nb)
{
	nb = (nb << 8) | (nb >> 8);
	return (nb);
}

uint32_t	swap_uint32(uint32_t nb)
{
	nb = ((nb & 0x000000FF) << 24 |
				(nb & 0x0000FF00) << 8 |
				(nb & 0x00FF0000) >> 8 |
				(nb & 0xFF000000) >> 24);
	return (nb);
}

uint64_t	swap_uint64(uint64_t nb)
{
	nb = ((nb & 0x00000000000000FF) << 56 |
				(nb & 0x000000000000FF00) << 40 |
				(nb & 0x0000000000FF0000) << 24 |
				(nb & 0x00000000FF000000) << 8 |
				(nb & 0x000000FF00000000) >> 8 |
				(nb & 0x0000FF0000000000) >> 24 |
				(nb & 0x00FF000000000000) >> 40 |
				(nb & 0xFF00000000000000) >> 56);
	return (nb);
}


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

t_cmd *has_fucked_up_order_cmds(t_env *env)
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

