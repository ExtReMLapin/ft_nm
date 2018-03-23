/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 10:09:16 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/23 10:49:44 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

/*
** Is in the ascii table, a > b ?
*/

bool		isstrbigger(char *a, char *b)
{
	int	i;

	i = 0;
	if (!b || !a)
		failmessage("Attempt to cmp two string is bigger but one is invalid\n");
	if (strcmp(a, b) == 0)
		return (false);
	while (a[i] && b[i])
	{
		if (a[i] > b[i])
			return (true);
		if (a[i] < b[i])
			return (false);
		i++;
	}
	if (b[i] == '\0')
		return (true);
	else
		return (false);
}
