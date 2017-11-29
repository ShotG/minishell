/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:26:01 by vartyukh          #+#    #+#             */
/*   Updated: 2017/04/02 20:26:03 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		work_shell_env(char **av, char **ev)
{
	char	**env;
	int		i;

	if (av == NULL)
	{
		i = -1;
		while (ev[++i] != NULL)
			ft_putendl(ev[i]);
	}
	env = rewrite_ev(ev);
	work_shell_env_det(av, &env);
	free_av_ev(NULL, env, 0, 1);
	exit(0);
}

void	set_mem_env_i(char **a)
{
	int i;

	i = -1;
	while (a[++i] != NULL)
		a[i][0] = 0;
}

int		work_shell_env_det(char **av, char ***ev)
{
	int res;

	res = 228;
	if (check_commnd(av, ev))
		;
	else if (!(res = exec_path_full(av, *ev)) || res == 1)
		;
	else if (!read_inp(av, ev))
		;
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	return (0);
}

int		check_env_flgs(char *s, int n)
{
	char	*f;
	int		i;

	f = "iu";
	if (n)
	{
		i = 0;
		while (s[++i] != 0)
		{
			if (!ft_strchr(f, s[i]))
			{
				ft_putendl_fd("env: illegal option -- ", 2);
				write(2, &(s[i]), 1);
				write(2, "\n", 1);
				ft_putendl_fd("usage: env [utility [argument ...]]", 2);
				return (-1);
			}
		}
		return (0);
	}
	else
	{
		ft_putendl_fd("usage: env [-iu] [u: name] [utility [argument ...]]", 2);
		exit(-1);
	}
}

void	commnd_unsetenv(char **av, char ***ev)
{
	int i;

	if (av[1] == NULL)
	{
		i = -1;
		while ((*ev)[++i] != NULL)
			ft_putendl((*ev)[i]);
		return ;
	}
	i = 0;
	while ((*ev)[i] != NULL && ft_strncmp((*ev)[i], av[1], ft_strlen(av[1])))
		i++;
	if ((*ev)[i] == NULL)
		return ;
	*ev = unset_ev(*ev, av[1]);
}