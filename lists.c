/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 10:52:46 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/15 11:13:12 by pfichepo         ###   ########.fr       */
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
		return;
	while (env->list->next)
	{
		cur = env->list;
		while (cur->next)
		{
			curnext = cur;
			cur = cur->next;
			curnext->next = NULL;
		}
		free(cur);
		cur = NULL;
	}
	free(env->list);
	env->list = NULL;
}