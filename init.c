/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:24:38 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/28 12:19:09 by pfichepo         ###   ########.fr       */
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



void	print_hex(uint64_t hex, bool first, bool is64)
{
	char 	hex_chars[16];
	int		i;

	i = 0;
	if (hex == 0x0 && first)
	{
		while (i < (8 + ((int)is64*8)) && first)
		{
			putchar(' ');
			i++;
		}
		return;
	}
	else
	{
		while (i < (4 + ((int)is64*3)) && first)
		{
			putchar('0');
			i++;
		}
	}
	memcpy(hex_chars, "0123456789abcdef", sizeof(char) * 16);
	if (hex > 15u)
	{
		print_hex(hex / 16u, false, is64);
		print_hex(hex % 16u, false, is64);
	}
	else
		putchar(hex_chars[hex]);
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
	//order_cmds(env);
	cmds = env->list;
	while (cmds)
	{
		if (strcmp(cmds->name, "radr://5614542") != 0)
		{
			print_hex(cmds->adr, true, env->is64bit);
			printf(" %c %s\n", cmds->symbol , cmds->name);
		}
		cmds = cmds->next;
	}
	return (env);
}
