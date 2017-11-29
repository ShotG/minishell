/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 13:08:56 by vartyukh          #+#    #+#             */
/*   Updated: 2017/01/14 13:21:38 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			check_str(char **str, char **line)
{
	char *p;
	char *tmp;

	if (*str == NULL)
		return (0);
	if ((p = ft_strchr(*str, '\n')))
	{
		*p = 0;
		*line = ft_strdup(*str);
		tmp = ft_strdup(p + 1);
		free(*str);
		*str = tmp;
		p = NULL;
		return (1);
	}
	return (0);
}

int			check_buff_for_end(char **buff, char **str, char **line)
{
	char *p;
	char *tmp;

	if ((p = ft_strchr(*buff, '\n')))
	{
		*p = 0;
		*line = ft_strjoin(*str, *buff);
		tmp = ft_strdup(p + 1);
		free(*str);
		*str = tmp;
		p = NULL;
		free(*buff);
		return (1);
	}
	return (0);
}

int			read_fd(int const fd, char **buff, char **str, char **line)
{
	ssize_t bytes;
	char	*tmp;

	while ((bytes = read(fd, *buff, BUFF_SIZE)) > 0)
	{
		if (*str == NULL)
			*str = ft_strdup("");
		(*buff)[bytes] = 0;
		if (check_buff_for_end(buff, str, line))
			return (1);
		tmp = ft_strdup(*str);
		free(*str);
		*str = ft_strjoin(tmp, *buff);
		free(tmp);
	}
	if (bytes == 0 && (*str == NULL || (*str)[0] == 0))
		return (0);
	if (bytes < 0)
		return (-1);
	return (2);
}

int			get_next_line(int const fd, char **line)
{
	static char		*s = NULL;
	char			*buff;
	int				res;

	if (fd < 0 || !(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	if (check_str(&s, line))
		return (1);
	res = read_fd(fd, &buff, &s, line);
	if (res == 1)
		return (1);
	else if (res == -1)
		return (-1);
	else if (res == 0)
		return (0);
	free(buff);
	if (s == NULL || res == 0)
		return (0);
	*line = ft_strdup(s);
	free(s);
	s = NULL;
	return (1);
}
