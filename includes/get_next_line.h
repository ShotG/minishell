/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 13:09:12 by vartyukh          #+#    #+#             */
/*   Updated: 2017/01/15 15:04:19 by vartyukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GET_NEXT_LINE_H
# define __GET_NEXT_LINE_H
# define BUFF_SIZE 32

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

int					get_next_line(int const fd, char **line);

typedef	struct		s_gnlstr
{
	char			*data;
	int				fd_s;
	struct s_gnlstr	*next;
}					t_gnlstr;

#endif
