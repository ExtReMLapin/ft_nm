/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:23 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/28 11:47:32 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	handle_fat(t_env *env)
{
	printf("%s\n", "handle_fat");
	handle_64(env);
}

void	handle_fatr(t_env *env)
{
	printf("%s\n", "handle_fatr");
	handle_64(env);
}