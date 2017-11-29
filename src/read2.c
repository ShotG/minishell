/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:41:39 by vartyukh          #+#    #+#             */
/*   Updated: 2017/04/02 20:41:41 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_commnd(char **av, char ***envp)
{
	if (!ft_strcmp(av[0], "cd"))
	{
		commnd_cd(av, envp);
		return (1);
	}
	if (!ft_strcmp(av[0], "echo"))
	{
		commnd_echo(av, *envp);
		return (1);
	}
	if (!ft_strcmp(av[0], "env"))
	{
		commnd_env(av, *envp);
		return (1);
	}
	return (check_commnd_s(av, envp));
}

int		check_commnd_s(char **av, char ***envp)
{
	if (!ft_strcmp(av[0], "setenv"))
	{
		commnd_setenv(av, envp);
		return (1);
	}
	if (!ft_strcmp(av[0], "unsetenv"))
	{
		commnd_unsetenv(av, envp);
		return (1);
	}
	return (0);
}

char	**add_ev(char **ev, char *s)
{
	int		i;
	char	**d;

	i = -1;
	while (ev[++i] != NULL)
		;
	d = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (ev[++i] != NULL)
		d[i] = ft_strdup(ev[i]);
	d[i++] = s;
	d[i] = NULL;
	i = -1;
	while (ev[++i] != NULL)
		free(ev[i]);
	free(ev[i]);
	free(ev);
	return (d);
}

char	**unset_ev(char **ev, char *s)
{
	int		i;
	int		j;
	char	**d;

	i = -1;
	while (ev[++i] != NULL)
		;
	d = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	j = 0;
	while (ev[i] != NULL)
	{
		if (ft_strncmp(ev[i], s, ft_strlen(s)))
			d[j++] = ft_strdup(ev[i++]);
		else
			i++;
	}
	d[j] = NULL;
	i = -1;
	while (ev[++i] != NULL)
		free(ev[i]);
	free(ev[i]);
	free(ev);
	return (d);
}

int		exec_path_full(char **av, char **ev)
{
	if (!access(av[0], F_OK))
	{
		if (!access(av[0], X_OK))
		{
			create_proc(av[0], av, ev);
			return (0);
		}
		else
		{
			ft_putstr_fd(av[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			return (1);
		}
	}
	else
		return (-1);
}
