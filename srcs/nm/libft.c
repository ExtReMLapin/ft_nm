/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 09:52:06 by pfichepo          #+#    #+#             */
/*   Updated: 2018/03/29 10:57:58 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

int		ft_atoi(const char *str)
{
	int i;
	int nbr;
	int negative;

	nbr = 0;
	negative = 0;
	i = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
			(str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		negative = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		nbr *= 10;
		nbr += (int)str[i] - '0';
		i++;
	}
	if (negative == 1)
		return (-nbr);
	else
		return (nbr);
}

void	ft_putcmdname(char *c)
{
	bool special;

	special = (COLORS == 1 && (ft_strcmp(c, "__mh_execute_header") == 0 ||
		ft_strcmp(c, "___stack_chk_fail") == 0 ||
		ft_strcmp(c, "___stack_chk_guard") == 0 ||
		ft_strcmp(c, "dyld_stub_binder") == 0));
	if (special)
		ft_putstr("\e[7m");
	ft_putstr(c);
	if (special)
		ft_putstr("\e[0m");
}
