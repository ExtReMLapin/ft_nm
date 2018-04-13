/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:52:46 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/21 11:32:47 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

/*
** NOT EFFICIENT BUT IDC
*/

void		clearlist(t_env *env)
{
	t_cmd *cur;
	t_cmd *curnext;

	if (!env->list)
		return ;
	while (env->list->next)
	{
		cur = env->list;
		while (cur->next)
		{
			curnext = cur;
			cur = cur->next;
		}
		free(cur);
		curnext->next = NULL;
	}
	free(env->list);
	env->list = NULL;
}

void		clearsections(t_env *env)
{
	t_section *sec;
	t_section *sec2;

	env->section->last = NULL;
	if (env->section->first == NULL)
		return ;
	while (env->section->first->next)
	{
		sec = env->section->first;
		while (sec->next)
		{
			sec2 = sec;
			sec = sec->next;
		}
		free(sec);
		sec2->next = NULL;
	}
	free(env->section->first);
	env->section->first = NULL;
	free(env->section);
	env->section = NULL;
}
