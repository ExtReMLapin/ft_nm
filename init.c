/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:24:38 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/08 11:41:10 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <nm.h>

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

void 	init_commands(t_env *env)
{
	if (env->is64bit)
	{
		if (env->isswap)
			handle_64(env, env->ptr, env->end, true);
		else
			handle_64(env, env->ptr, env->end, false);
	}
	else if (!env->isfattype)// 32bits non fat
	{
		if (env->isswap) // swapped 32bits
			handle_32(env, env->ptr, env->end, true);
		else //32bits
			handle_32(env, env->ptr, env->end, false);
	}
	else // fat
	{
		if (env->isswap) // swapped fat
			handle_fat(env, true);
		else //fat
			handle_fat(env, false);
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
	if (!env->is64bit && !env->isswap && !env->isfattype && *(uint32_t*)ptr != MH_MAGIC)
		failmessage("File not recognized");

	env->list = NULL;
	init_commands(env);
	
	order_cmds(env);
	cmds = env->list;
	while (cmds)
	{
		#ifdef COLORS
			printf("%s", "\033[0;31m");
		#endif
		print_hex(cmds->adr, true, env);
		#ifdef COLORS
			printf("%s", "\033[0;0m");
		#endif
		printf(" %c %s\n", cmds->symbol , cmds->name);
		cmds = cmds->next;
	}
	return (env);
}
