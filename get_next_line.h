/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 11:12:27 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/14 21:20:54 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct	s_gnlfd
{
	char			*buff;
	int				fd;
	int				length;
	int				offset;
	int				i;
	struct s_gnlfd	*next;
}				t_gnlfd;

# ifndef EOF
#  define EOF			-1
# endif

# define GNL_BUFF		512

# define GNL_SUCCES		1
# define GNL_EOF		0
# define GNL_ERROR		-1

int				get_next_line(int const fd, char **line);

#endif
