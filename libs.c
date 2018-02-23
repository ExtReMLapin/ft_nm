/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/23 10:59:00 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		failmessage(char *message)
{
	printf("%s\n",message);
	exit(EXIT_FAILURE);
}

/*
** I could have just swaped internal struct variables instead of making this hack, but i didn't
** The same way i could have just malloced the number of cmds instead of making a linked list
*/

void 	swapcmds(t_cmd *a, t_cmd *b)
{
	t_cmd *tmp;

	if (!b || !a)
		failmessage("Attempt to swap two cmds one is invalid");
	if (a->next)
		a->next->past = b;
	if (a->past)
		a->past->next = b;

	if (b->next)
		b->next->past = a;
	if (b->past)
		b->past->next = a;

	tmp = a->next;
	a->next = b->next;
	b->next = tmp;

	tmp = a->past;
	a->past = b->past;
	b->past = tmp;
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
		i++;
	}
	if (b[i] == '\0')
		return (false);
	else
		return (true);
}

