/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:12:45 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/29 10:43:44 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

char						*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	while (src[len])
		len++;
	str = (char*)malloc(sizeof(*str) * (len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void						add_list(char *name, t_lsection *list)
{
	t_section	*add;

	if ((add = (t_section*)malloc(sizeof(t_section))) == NULL)
		return ;
	add->name = ft_strdup(name);
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

void						add_segment64(\
		struct segment_command_64 *com, t_lsection *list, bool swap)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;
	seg = (struct segment_command_64*)com;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	com->nsects = (swap) ? swap_uint64(com->nsects) : com->nsects;
	while (i < com->nsects)
	{
		add_list(sec->sectname, list);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void						add_segment32(\
		struct segment_command *com, t_lsection *list, bool swap)
{
	unsigned int			i;
	struct section			*sec;
	struct segment_command	*seg;

	i = 0;
	seg = (struct segment_command*)com;
	sec = (struct section*)(seg + sizeof(seg) / sizeof(void*));
	com->nsects = (swap) ? swap_uint32(com->nsects) : com->nsects;
	while (i < com->nsects)
	{
		add_list(sec->sectname, list);
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
		i++;
	}
}

void						*ft_memcpy(void *dst,
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
