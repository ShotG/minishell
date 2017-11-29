/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:43:15 by vartyukh          #+#    #+#             */
/*   Updated: 2017/11/29 20:43:16 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_row(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	commnd_setenv(char **av, char ***envp)
{
	int		i;
	char	*t;
	char	*s;

	if (count_row(av) < 3 || count_row(av) > 3)
		ft_putendl_fd(
			"setenv: wrong number of parameter\nusage: setenv <KEY> <VALUE>", 2
		);
	else
	{
		s = ft_strdup(av[1]);
		t = s;
		s = ft_strjoin(s, "=");
		free(t);
		setenv_norm(&t, &s, av);
		i = 0;
		while ((*envp)[i] != NULL &&
		(ft_strncmp((*envp)[i], av[1], ft_strlen(av[1]))))
			i++;
		if ((*envp)[i] != NULL)
			*envp = unset_ev(*envp, av[1]);
		*envp = add_ev(*envp, s);
	}
}

void	setenv_norm(char **t, char **s, char **av)
{
	char	*kek;
	int		i;
	int		j;

	kek = ft_strnew(ft_strlen(av[2]));
	i = 0;
	j = 0;
	while (av[2][i] != 0)
	{
		if (av[2][i] == '\"')
			i++;
		else
		{
			kek[j] = av[2][i];
			i++;
			j++;
		}
	}
	if (av[2] != NULL)
	{
		*t = *s;
		*s = ft_strjoin(*s, kek);
		free(*t);
		free(kek);
	}
}