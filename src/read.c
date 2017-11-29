/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:40:33 by vartyukh          #+#    #+#             */
/*   Updated: 2017/04/02 20:40:34 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		read_inp(char **av, char ***env)
{
	int		i;
	int		j;
	char	**t;
	int		res;

	i = 0;
	if ((*env)[0] == NULL)
		return (-1);
	while ((*env)[i] != NULL && (ft_strncmp((*env)[i], "PATH", 4)))
		i++;
	if ((*env)[i] == NULL)
		return (-1);
	j = 0;
	while ((*env)[i][j] != 0 && (*env)[i][j] != '=')
		j++;
	if ((*env)[i][j] != '=')
		return (-1);
	t = ft_strsplit(&((*env)[i][++j]), ':');
	res = exec_path(av, t, *env);
	i = -1;
	while (t[++i] != NULL)
		free(t[i]);
	free(t);
	return (res);
}

int		create_proc(char *path, char **av, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, av, env);
		ft_putstr_fd(av[0], 2);
		ft_putendl_fd(": An error occurred", 2);
		return (-1);
	}
	else
	{
		wait(0);
	}
	return (0);
}

int		exec_path(char **av, char **t, char **env)
{
	int		i;
	char	*pth;

	i = -1;
	while (t[++i] != NULL)
	{
		pth = build_path(t[i], av[0]);
		if (!access(pth, F_OK))
		{
			if (!access(pth, X_OK))
			{
				create_proc(pth, av, env);
				free(pth);
				return (0);
			}
			else
			{
				free(pth);
				ft_putstr_perm_d(av);
				return (-1);
			}
		}
		free(pth);
	}
	return (1);
}

void	ft_putstr_perm_d(char **av)
{
	ft_putstr_fd(av[0], 2);
	ft_putendl_fd(": Permission denied", 2);
}

char	*build_path(char *str, char *name)
{
	int		i;
	char	*res;
	char	*t;

	res = ft_strdup(str);
	i = 0;
	while (res[i] != 0)
		i++;
	if (res[i - 1] != '/')
	{
		t = res;
		res = ft_strjoin(t, "/");
		free(t);
	}
	t = res;
	res = ft_strjoin(t, name);
	free(t);
	return (res);
}
