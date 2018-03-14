/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:58:07 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/14 10:11:19 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>



static void						add_list(char *name, t_lsection *list)
{
	t_section	*add;

	if ((add = (t_section*)malloc(sizeof(t_section))) == NULL)
		return ;
	add->name = strdup(name);
	add->next = NULL;
	if (list->first == NULL)
	{
		list->first = add;
		list->last = add;
		add->nb = 1;
	}
	else
	{
		add->nb = list->last->nb + 1;
		list->last->next = add;
		list->last = add;
	}
}

static void						add_segment(\
									struct segment_command_64 *com, t_lsection *list)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;

	seg = (struct segment_command_64*)com;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	while (i < com->nsects)
	{
		add_list(sec->sectname, list);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}



static char			secto(t_lsection *sec, unsigned int n_sect)
{ 
	t_section		*tmp;

	tmp = sec->first;

	while (tmp) 
	{
		if (tmp->nb == n_sect)
		{
			if (!strcmp(tmp->name, SECT_DATA))
				return ('D');
			else if (!strcmp(tmp->name, SECT_BSS))
				return ('B');
			else if (!strcmp(tmp->name, SECT_TEXT))
				return ('T');
			else
			{

				return ('S');
			}
			//printf("aaa %s\n", tmp->name);
		}
		tmp = tmp->next;
	}
	//printf("%s %p\n", "fail return", tmp);
	return ('S');
}



char				typing(uint32_t type, uint32_t n_sect, t_lsection *sec, int addr)
{
	char			ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_TYPE) == N_SECT)
		ret = secto(sec, n_sect);
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}





static void add_output(int nsyms, void *symoff, void *stroff, t_env* env)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;
	t_cmd			*cmd;

	array = (void*)symoff;
	stringtable = (void*)stroff;
	cmd = NULL;
	for (i = 0; i < nsyms; ++i)
	{
		if (((void*)&array[i] + sizeof(*array) > (void*)env->end) || (void*)stringtable > (void*)env->end)
			failmessage("Please check file integrity");
		mlccmd(env, array[i].n_value, typing (array[i].n_type, array[i].n_sect, env->section, array[i].n_value), stringtable + array[i].n_un.n_strx);
	}
}

void	handle_64(t_env *env, char *adr, char* max, bool swap)
{
	int 	ncmds;
	struct	mach_header_64 *header;
	struct  load_command *lc;
	int		i;
	struct symtab_command *sym;

	header = (struct mach_header_64*)adr;
	if ((void*)header > (void*)max)
		failmessage("Fail header");
	ncmds = (swap) ? swap_uint32(header->ncmds) : header->ncmds;
	lc = (struct  load_command*)(header+1);
	if ((env->section  = (t_lsection*)malloc(sizeof(t_lsection))) == NULL)
		return;
	env->section ->first = NULL;
	env->section ->last = NULL;


	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SEGMENT_64)
			add_segment((struct segment_command_64*)lc, env->section );
		lc = (void*)lc + lc->cmdsize;
	}

	lc = (struct  load_command*)(header+1);
	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			add_output(sym->nsyms, (void*)adr + sym->symoff, (void*)adr + sym->stroff, env);
		}
		lc = (void*)lc + lc->cmdsize;
	}
}
