/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 16:01:32 by jaguillo          #+#    #+#             */
/*   Updated: 2014/12/30 16:01:33 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void			ft_putendl(char *str)
{
	int				len;

	len = 0;
	while (str[len] != '\0')
		len++;
	str[len] = '\n';
	write(1, str, len + 1);
	str[len] = '\0';
}

int				main(int argc, char **argv)
{
	int				fd;
	char			*line;

	argv++;
	while (--argc > 0)
	{
		fd = open(*(argv++), O_RDONLY);
		while (get_next_line(fd, &line) > 0)
		{
			ft_putendl(line);
			free(line);
		}
		close(fd);
	}
	return (0);
}
/*
int				main(int argc, char **argv)
{
	int				fd[argc];
	int				fd_count;
	int				loop;
	int				i;
	char			*line;

	fd_count = 0;
	argv++;
	while (--argc > 0)
		fd[fd_count++] = open(*(argv++), O_RDONLY);
	loop = 1;
	while (loop)
	{
		loop = 0;
		i = -1;
		while (++i < fd_count)
			if (get_next_line(fd[i], &line) > 0)
			{
				ft_putendl(line);
				free(line);
				loop = 1;
			}
	}
	return (0);
}
*/
