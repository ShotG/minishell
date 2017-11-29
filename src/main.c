/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:27:08 by vartyukh          #+#    #+#             */
/*   Updated: 2017/04/02 20:27:09 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	free_av_ev(char **av, char **ev, int l, int r)
{
	int i;

	if (l)
	{
		i = -1;
		while (av[++i] != NULL)
			free(av[i]);
		free(av);
	}
	if (r)
	{
		i = -1;
		while (ev[++i] != NULL)
			free(ev[i]);
		free(ev);
	}
}

char	**rewrite_ev(char **ev)
{
	int		i;
	char	**d;

	i = -1;
	while (ev[++i] != NULL)
		;
	d = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (ev[++i] != NULL)
	{
		d[i] = ft_strdup(ev[i]);
	}
	d[i] = NULL;
	return (d);
}

int		work_shell(char **av, char ***ev, char *s, int *ret)
{
	int res;

	res = 228;
	if (!(ft_strcmp(av[0], "exit")))
	{
		(av[1] != NULL) ? (*ret = ft_atoi(av[1])) : 0;
		free(s);
		free_av_ev(av, *ev, 1, 0);
		return (-1);
	}
	else if (!(res = exec_path_full(av, *ev)) || res == 1)
		;
	else if (check_commnd(av, ev))
		;
	else if (!read_inp(av, ev))
		;
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	int		i;
	char	*s;
	char	**av;
	char	**ev;
	int		ret;

	ret = 0;
	if (argc == 1 && argv[1] == NULL)
	{
		start();
		ev = rewrite_ev(envp);
		while (1)
		{
			write(1, "$> ", 3);
			if (!(i = get_next_line(0, &s)) || !ft_strcmp(s, ""))
			{
				free(s);
				continue ;
			}
			av = splitspaces(s);
			if (work_shell(av, &ev, s, &ret))
				break ;
			free(s);
			free_av_ev(av, ev, 1, 0);
		}
		free_av_ev(av, ev, 0, 1);
	}
	return (ret);
}
