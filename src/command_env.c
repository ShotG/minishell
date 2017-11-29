/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:36:21 by vartyukh          #+#    #+#             */
/*   Updated: 2017/11/29 20:36:26 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commnd_env(char **av, char **envp)
{
	int		i;
	pid_t	pid;

	if (av[1] == NULL)
	{
		i = -1;
		while (envp[++i] != NULL)
			ft_putendl(envp[i]);
		return ;
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			env_norm(av, envp);
		}
		else
			wait(0);
	}
}