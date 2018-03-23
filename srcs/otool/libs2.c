/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 12:27:47 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/23 11:33:17 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

/*
** Pas copié collé, c'est pas vrai, zavé pa dpreuvs
*/

uint16_t	swap_uint16(uint16_t nb)
{
	nb = (nb << 8) | (nb >> 8);
	return (nb);
}

uint32_t	swap_uint32(uint32_t nb)
{
	nb = ((nb & 0x000000FF) << 24 |
				(nb & 0x0000FF00) << 8 |
				(nb & 0x00FF0000) >> 8 |
				(nb & 0xFF000000) >> 24);
	return (nb);
}

uint64_t	swap_uint64(uint64_t nb)
{
	nb = ((nb & 0x00000000000000FF) << 56 |
				(nb & 0x000000000000FF00) << 40 |
				(nb & 0x0000000000FF0000) << 24 |
				(nb & 0x00000000FF000000) << 8 |
				(nb & 0x000000FF00000000) >> 8 |
				(nb & 0x0000FF0000000000) >> 24 |
				(nb & 0x00FF000000000000) >> 40 |
				(nb & 0xFF00000000000000) >> 56);
	return (nb);
}

void		failmessage(char *message)
{
	write(1, message, strlen(message));
	exit(EXIT_FAILURE);
}
