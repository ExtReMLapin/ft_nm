/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:24:38 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/28 11:23:47 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

/*
** Put the cmd data at the end of the existing list
*/

void	init_commands(t_env *env)
{
	if (!env->isfattype && !env->isarchive)
	{
		ft_putstr(env->file_name);
		ft_putstr(":\n");
	}
	if (env->isarchive)
	{
		ft_putstr("Archive : ");
		ft_putstr(env->file_name);
		ft_putchar('\n');
		handle_ar(env->ptr, env->end, env);
		return ;
	}
	if (env->is64bit)
		handle_64(env->ptr, env->end, env->isswap, env);
	else if (!env->isfattype)
		handle_32(env->ptr, env->end, env->isswap, env);
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
		return (NULL);
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
		return (NULL);
	init_commands(env);
	return (env);
}

void	*ft_memcpy(void *dst,
	const void *src, size_t n)
{
	unsigned int	i;
	char			*dest;
	const char		*sourc;

	if (src == NULL || dst == NULL)
		return (NULL);
	dest = dst;
	sourc = src;
	i = 0;
	while (i < n)
	{
		dest[i] = sourc[i];
		i++;
	}
	return (dst);
}
