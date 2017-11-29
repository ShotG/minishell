/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:00:04 by vartyukh          #+#    #+#             */
/*   Updated: 2017/11/29 20:00:06 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commnd_echo(char **av, char **ev)
{
	int i;

	i = 0;
	while (av[++i] != NULL)
	{
		ft_putstr_echo(av[i], ev);
		(av[i + 1] == NULL) ? 0 : write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	ft_putstr_echo(char *s, char **ev)
{
	int i;
	int j;
	int n;
	int k;

	i = -1;
	while (s[++i] != 0)
	{
		if (s[i] == '$')
		{
			j = i + 1;
			while (s[j] != 0 && !((s[i] >= '\t' && s[i] <= '\r')
			|| s[i] == ' '))
				j++;
			n = i + 1;
			k = 0;
			while (ev[k] != NULL && (ft_strncmp(ev[k], &(s[n]), (j - n))))
				k++;
			if (ev[k] != NULL)
				ft_putstr_echo_norm(ev, k);
			i = j;
		}
		else
			(s[i] != '\"') ? (write(1, &(s[i]), 1)) : 0;
	}
}

void	ft_putstr_echo_norm(char **ev, int k)
{
	int n;

	n = 0;
	while (ev[k][n] != 0 && ev[k][n] != '=')
		n++;
	(ev[k][n] != 0) ? n++ : 0;
	ft_putstr(&(ev[k][n]));
}