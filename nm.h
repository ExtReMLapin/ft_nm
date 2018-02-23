/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 10:49:33 by pfichepo          #+#    #+#             */
/*   Updated: 2018/02/23 11:11:31 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>

typedef struct 				s_cmd
{
	uint64_t				adr;
	char					symbol;
	char					*name;
	struct s_cmd			*past;
	struct s_cmd			*next;
}							t_cmd;

typedef struct				s_env
{
	bool					is64bit;
	bool					isswap;
	bool					isfattype;					
	char					*ptr;
	char					*end;
	t_cmd 					*list;
}							t_env;


void						handle_64(t_env *env);
void 						mlccmd(t_env *env, uint64_t n_value, char symbol, char *name);
t_env 						*make_env(char *ptr, char* end);
char 						get_symbol(uint8_t value);
void						handle_64(t_env *env);
void						handle_64r(t_env *env);
void						handle_32(t_env *env);
void						handle_32r(t_env *env);
void						handle_fat(t_env *env);
void						handle_fatr(t_env *env);
void						failmessage(char *message);
void						order_cmds(t_env *env);
#endif