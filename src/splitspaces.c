/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitspaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:27:40 by vartyukh          #+#    #+#             */
/*   Updated: 2017/04/02 20:27:42 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_cwords(char const *s)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (0);
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	while (s[i] != '\0')
	{
		if ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		{
			i++;
			count++;
			while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
				i++;
		}
		else
			i++;
	}
	if (!((s[i - 1] >= '\t' && s[i - 1] <= '\r') || s[i - 1] == ' '))
		count++;
	return (count);
}

char	*ft_strcreate(char const *s, char *arr, int n)
{
	int j;

	j = 0;
	while (!((s[n + j] >= '\t' && s[n + j] <= '\r') || s[n + j] == ' ')
	&& s[n + j] != '\0')
		j++;
	arr = (char *)malloc(sizeof(char) * (j + 1));
	arr[j] = '\0';
	j = 0;
	while (!((s[n] >= '\t' && s[n] <= '\r') || s[n] == ' ') && s[n] != '\0')
		arr[j++] = s[n++];
	return (arr);
}

char	**splitspaces(char const *s)
{
	char	**arr;
	size_t	i;
	int		n;
	int		j;

	if (s == NULL)
		return (0);
	i = ft_cwords(s);
	if (!(arr = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	n = 0;
	i = 0;
	while (i < ft_cwords(s))
	{
		while (((s[n] >= '\t' && s[n] <= '\r') || s[n] == ' '))
			n++;
		j = 0;
		arr[i] = ft_strcreate(s, arr[i], n);
		while (!((s[n + j] >= '\t' && s[n + j] <= '\r')
		|| s[n + j] == ' ') && s[n + j] != '\0')
			n++;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	env_norm(char **av, char **envp)
{
	if (av[1][0] != '-')
		work_shell_env(++av, envp);
	else
	{
		if (check_env_flgs(av[1], 1))
		{
			exit(0);
		}
		else
		{
			if (ft_strchr(av[1], 'i'))
			{
				set_mem_env_i(envp);
				work_shell_env((av + 2), envp);
			}
			else
				env_norm_s(av, envp);
		}
	}
}

void	env_norm_s(char **av, char **envp)
{
	int i;

	if (av[2] == NULL)
		check_env_flgs(av[1], 0);
	else
	{
		envp = unset_ev(envp, av[2]);
		if ((av[3]) == NULL)
		{
			i = -1;
			while (envp[++i] != NULL)
				ft_putendl(envp[i]);
			exit(0);
		}
		else
			work_shell_env((av + 3), envp);
	}
}
