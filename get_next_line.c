/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 11:12:36 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/06 23:41:55 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static void		gnl_memcpy(const void *dst, const void *src, int len)
{
	while (len > 7)
	{
		*((unsigned long long int*)dst) = *((unsigned long long int*)src);
		dst += 8;
		src += 8;
		len -= 8;
	}
	while (len-- > 0)
		*((unsigned char*)(dst++)) = *((unsigned char*)(src++));
}

static t_gnlfd	*get_gnlfd(int const fd)
{
	static t_gnlfd	*gnlfd_list = NULL;
	t_gnlfd			*tmp;

	tmp = gnlfd_list;
	while (tmp != NULL)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if ((tmp = (t_gnlfd*)malloc(sizeof(t_gnlfd))) == NULL)
		return (NULL);
	*tmp = (t_gnlfd){NULL, fd, 0, 0, -1, gnlfd_list};
	gnlfd_list = tmp;
	return (tmp);
}

static int		buff_read(t_gnlfd *gnlfd)
{
	char			*tmp;
	int				len;

	if ((tmp = (char*)malloc(gnlfd->length + GNL_BUFF + 1)) == NULL)
		return (-1);
	gnl_memcpy(tmp, gnlfd->buff, gnlfd->length);
	if (gnlfd->buff != NULL)
		free(gnlfd->buff - gnlfd->offset);
	gnlfd->buff = tmp;
	len = read(gnlfd->fd, tmp + gnlfd->length, GNL_BUFF);
	tmp[gnlfd->length + GNL_BUFF] = '\0';
	gnlfd->length += (len < 0) ? 0 : len;
	gnlfd->offset = 0;
	gnlfd->i = -1;
	return (len);
}

static int		buff_cut(t_gnlfd *gnlfd, int len, char **dst, int rem)
{
	*dst = gnlfd->buff;
	(*dst)[len] = '\0';
	len += rem;
	gnlfd->offset += len;
	gnlfd->buff += len;
	gnlfd->length -= len;
	return (GNL_SUCCES);
}

int				get_next_line(int const fd, char **line)
{
	t_gnlfd			*gnl;
	int				len;

	if (fd >= 0 && line != NULL && (gnl = get_gnlfd(fd)) != NULL)
		while (1)
		{
			while (++(gnl->i) < gnl->length)
				if (gnl->buff[gnl->i] == '\n' || gnl->buff[gnl->i] == EOF)
					return (buff_cut(gnl, gnl->i, line, 1));
			if ((len = buff_read(gnl)) < 0)
				break ;
			if (len == 0 && gnl->length == 0)
				return (*line = NULL, free(gnl->buff - gnl->offset),
				*gnl = (t_gnlfd){NULL, fd, 0, 0, -1, gnl->next}, GNL_EOF);
			if (len == 0)
				return (buff_cut(gnl, gnl->length, line, 0));
		}
	return (GNL_ERROR);
}
