/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:24:38 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/22 11:02:44 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "nm.h"
 

t_env *make_env(char *ptr, char* end)
{
	t_env *env;

	env = (t_env*)malloc(sizeof(t_env));
	env->ptr = ptr;
	env->end = end;
	env->is64bit = (*(int*)ptr == MH_MAGIC_64 || *(int*)ptr == MH_CIGAM_64);
	env->isswap = (*(int*)ptr == MH_CIGAM_64);
	env->isfattype = (*(int*)ptr == FAT_CIGAM || *(int*)ptr == FAT_MAGIC);
}



