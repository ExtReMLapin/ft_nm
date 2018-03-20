/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:24:38 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/20 12:42:40 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

/*
** Put the cmd data at the end of the existing list
*/

void	mlccmd(t_env *env, uint64_t n_value, char symbol, char *name)
{
	t_cmd *cmd;
	t_cmd *cmd2;

	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->adr = n_value;
	cmd->symbol = symbol;
	cmd->name = name;
	cmd->next = NULL;
	if (env->list == NULL)
	{
		env->list = cmd;
		return ;
	}
	cmd2 = env->list;
	while (cmd2->next)
		cmd2 = cmd2->next;
	cmd2->next = cmd;
}

void	init_commands(t_env *env)
{
	if ((env->section = (t_lsection*)malloc(sizeof(t_lsection))) == NULL)
		return ;
	env->section ->first = NULL;
	env->section ->last = NULL;
	if (env->isarchive)
	{
		handle_ar(env->ptr, env->end, env);
		return ;
	}
	if (env->is64bit)
		handle_64(env, env->ptr, env->end, env->isswap);
	else if (!env->isfattype)
		handle_32(env, env->ptr, env->end, env->isswap);
	else
		handle_fat(env, env->isswap);
}

void handle_fat(t_env *env, bool swap)
{
	struct fat_header	*header;

	header = (struct fat_header*)env->ptr;
	if ((void*)header > (void*)env->end)
		failmessage("Fail header");
	if (!env->is64bit)
		handle_fat32(env, swap);
	else
		handle_fat64(env, swap);
}

t_env	*make_env(char *ptr, char *end, char *name)
{
	t_env *env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		failmessage("FailMalloc");
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
		failmessage("File not recognized");
	env->list = NULL;
	init_commands(env);
	return (env);
}
