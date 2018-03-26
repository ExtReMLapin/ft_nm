/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:24:38 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/26 12:49:36 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

/*
** Put the cmd data at the end of the existing list
*/



void	init_commands(t_env *env)
{
	ft_putstr(env->file_name);
	ft_putstr(":\n");
	if (env->isarchive)
	{
		handle_ar(env->ptr, env->end, env);
		return ;
	}
	if (env->is64bit)
		handle_64(env->ptr, env->end, env->isswap);
	else if (!env->isfattype)
		handle_32(env->ptr, env->end, env->isswap);
	else
		handle_fat(env, env->isswap);
}

void	handle_fat(t_env *env, bool swap)
{
	struct fat_header	*header;

	header = (struct fat_header*)env->ptr;
	if ((void*)header > (void*)env->end)
		failmessage("Fail header\n");
	if (!env->is64bit)
		handle_fat32(env, swap);
	else
		handle_fat64(env, swap);
}

t_env	*make_env(char *ptr, char *end, char *name)
{
	t_env *env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		failmessage("FailMalloc\n");
	env->file_name = name;
	env->ptr = ptr;
	env->end = end;
	env->is64bit = (*(uint32_t*)ptr == MH_MAGIC_64 ||
		*(uint32_t*)ptr == MH_CIGAM_64);
	env->isswap = (*(uint32_t*)ptr == MH_CIGAM_64 ||
		*(uint32_t*)ptr == MH_CIGAM || *(uint32_t*)ptr == FAT_CIGAM);
	env->isfattype = (*(uint32_t*)ptr == FAT_CIGAM ||
		*(uint32_t*)ptr == FAT_MAGIC);
	env->isarchive = check_ar_header(ptr);
	env->in_ppc = false;
	if (!env->isarchive && !env->is64bit && !env->isswap &&
		!env->isfattype && *(uint32_t*)ptr != MH_MAGIC)
		failmessage("File not recognized\n");
	init_commands(env);
	return (env);
}
