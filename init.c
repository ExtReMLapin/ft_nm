/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:24:38 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/23 12:42:44 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "nm.h"

/*
** Put the cmd data at the end of the existing list
*/

void 	mlccmd(t_env *env, uint64_t n_value, char symbol, char *name)
{
	t_cmd *cmd;
	t_cmd *cmd2;

	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->adr = n_value;
	cmd->symbol = symbol;
	cmd->name = name;
	cmd->next = NULL;
	cmd->past = NULL;
	if (env->list == NULL)
	{
		env->list = cmd;
		return ;
	}
	cmd2 = env->list;
	while (cmd2->next)
		cmd2 = cmd2->next;
	cmd2->next = cmd;
	cmd->past = cmd2;
}

void 	init_commands(t_env *env)
{
	if (env->is64bit)
	{
		if (env->isswap)
			handle_64r(env);
		else
			handle_64(env);
	}
	else if (!env->isfattype)// 32bits non fat
	{
		if (env->isswap) // swapped 32bits
			handle_32r(env);
		else //32bits
			handle_32(env);
	}
	else // fat
	{
		if (env->isswap) // swapped fat
			handle_fatr(env);
		else //fat
			handle_fatr(env);
	}
}

t_env *make_env(char *ptr, char* end)
{
	t_env *env;
	t_cmd *cmds;

	env = (t_env*)malloc(sizeof(t_env));
	env->ptr = ptr;
	env->end = end;
	env->is64bit = (*(uint32_t*)ptr == MH_MAGIC_64 || *(uint32_t*)ptr == MH_CIGAM_64);
	env->isswap = (*(uint32_t*)ptr == MH_CIGAM_64 || *(uint32_t*)ptr == MH_CIGAM || *(uint32_t*)ptr == FAT_CIGAM);
	env->isfattype = (*(uint32_t*)ptr == FAT_CIGAM || *(uint32_t*)ptr == FAT_MAGIC);
	env->list = NULL;
	init_commands(env);
	order_cmds(env);
	cmds = env->list;
	while (cmds)
	{
		printf("%#016llX %c %s\n",cmds->adr, cmds->symbol , cmds->name);
		cmds = cmds->next;

	}


	return (env);
}