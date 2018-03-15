/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:20:20 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/15 12:08:46 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

/*
** Called by fat files
*/

void nm2(t_env *env, char *ptr, char* max)
{
	uint32_t head;

	head = *(uint32_t*)ptr;
	clearlist(env);
	clearsections(env);
	if (head == MH_MAGIC_64)
		handle_64(env, ptr, max, false);
	else if (head == MH_CIGAM_64)
		handle_64(env, ptr, max, true);
	else if (head == MH_MAGIC)
		handle_32(env, ptr, max, false);
	else if (head == MH_CIGAM)
		handle_32(env, ptr, max, true);
	else
		failmessage("ohohoh, pas normal");
}