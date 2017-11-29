/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:47:58 by vartyukh          #+#    #+#             */
/*   Updated: 2017/04/02 20:48:00 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H
# define __MINISHELL_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>

int		read_inp(char **av, char ***env);
void	start(void);
int		exec_path(char **av, char **t, char **env);
char	*build_path(char *str, char *name);
char	**splitspaces(char const *s);
char	*ft_strcreate(char const *s, char *arr, int n);
size_t	ft_cwords(char const *s);
int		create_proc(char *path, char **av, char **env);
int		check_commnd(char **av, char ***envp);
int		work_com(char **av, char **envp);
void	commnd_cd(char **av, char ***ev);
void	commnd_echo(char **av, char **ev);
void	commnd_env(char **av, char **envp);
char	**rewrite_ev(char **ev);
void	free_av_ev(char **av, char **ev, int l, int r);
void	commnd_setenv(char **av, char ***envp);
char	**add_ev(char **ev, char *s);
void	commnd_unsetenv(char **av, char ***envp);
char	**unset_ev(char **ev, char *s);
int		work_shell(char **av, char ***ev, char *s, int *ret);
int		work_shell_env(char **av, char **ev);
int		work_shell_env_det(char **av, char ***ev);
int		check_env_flgs(char *s, int f);
void	set_mem_env_i(char **a);
int		exec_path_full(char **av, char **ev);
void	ft_putstr_echo(char *s, char **ev);
int		cd_home(char **ev, char **p);
int		cd_old(char **ev, char **p);
int		work_shell_spl(char ***av, char ***ev, char *s, int *ret);
char	*cd_null(char ***ev);
int		cd_norm(char **cpth, char *pth, int res, char **av);
void	setenv_norm(char **t, char **s, char **av);
void	env_norm(char **av, char **ev);
void	env_norm_s(char **av, char **envp);
void	ft_putstr_echo_norm(char **ev, int k);
void	ft_putstr_perm_d(char **av);
int		check_commnd_s(char **av, char ***envp);

#endif
