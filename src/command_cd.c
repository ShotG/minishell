/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:07:12 by vartyukh          #+#    #+#             */
/*   Updated: 2017/11/29 20:07:14 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commnd_cd(char **av, char ***ev)
{
	char	*pth;
	int		res;
	char	*cpth;
	char	*old_pth[3];

	if (av[1] == NULL)
	{
		if ((pth = cd_null(ev)) == NULL)
			return ;
	}
	else
		pth = ft_strdup(av[1]);
	res = 0;
	(pth[0] == '~') ? (res = cd_home(*ev, &pth)) : 0;
	(pth[0] == '-') ? (res = cd_old(*ev, &pth)) : 0;
	if (!(cd_norm(&cpth, pth, res, av)))
		return ;
	old_pth[1] = ft_strdup("OLDPWD");
	old_pth[2] = ft_strdup(cpth);
	commnd_setenv(old_pth, ev);
	free(pth);
	free(cpth);
	free(old_pth[1]);
	free(old_pth[2]);
}

char	*cd_null(char ***ev)
{
	int		j;
	int		i;
	char	*pth;

	i = 0;
	while ((*ev)[i] != NULL && (ft_strncmp((*ev)[i], "HOME", 4)))
		i++;
	if ((*ev)[i] == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (NULL);
	}
	else
	{
		j = 0;
		while ((*ev)[i][j] != 0 && (*ev)[i][j] != '=')
			j++;
		j++;
		pth = ft_strdup(&((*ev)[i][j]));
	}
	return (pth);
}

int		cd_home(char **ev, char **p)
{
	int		i;
	int		j;
	char	*pth;
	char	*t;

	i = 0;
	while (ev[i] != NULL && (ft_strncmp(ev[i], "HOME", 4)))
		i++;
	if (ev[i] == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (-1);
	}
	j = 0;
	while (ev[i][j] != 0 && ev[i][j] != '=')
		j++;
	j++;
	pth = ft_strdup(&(ev[i][j]));
	t = pth;
	pth = ft_strjoin(pth, (*p + 1));
	free(t);
	free(*p);
	*p = pth;
	return (0);
}

int		cd_old(char **ev, char **p)
{
	int		i;
	int		j;
	char	*pth;

	i = 0;
	while (ev[i] != NULL && (ft_strncmp(ev[i], "OLDPWD", 4)))
		i++;
	if (ev[i] == NULL)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (-1);
	}
	j = 0;
	while (ev[i][j] != 0 && ev[i][j] != '=')
		j++;
	j++;
	pth = ft_strdup(&(ev[i][j]));
	free(*p);
	*p = pth;
	return (0);
}

int		cd_norm(char **cpth, char *pth, int res, char **av)
{
	struct stat file_stat;

	if (res != 0)
		return (-1);
	*cpth = ft_strnew(512);
	getcwd(*cpth, 512);
	if (chdir(pth))
	{
		ft_putstr_fd("minishel: cd: ", 2);
		if ((stat(av[1], &file_stat) < 0))
			ft_putstr("No such file or directory: ");
		else if (!(S_ISDIR(file_stat.st_mode)))
			ft_putstr("Not a directory: ");
		else if ((access(av[1], R_OK) < 0))
			ft_putstr("Permission denied: ");
		else
			ft_putstr("An error occurred: ");
		ft_putendl_fd(pth, 2);
	}
	return (0);
}