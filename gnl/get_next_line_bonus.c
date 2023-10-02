/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyamad <mayyamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 02:40:41 by mayyamad          #+#    #+#             */
/*   Updated: 2023/06/13 12:11:24 by mayyamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_all(int fd, char *line)
{
	ssize_t	read_byte;
	char	*buf;

	read_byte = 1;
	while (!(ft_strchr(line, '\n')) && read_byte != 0)
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (buf == NULL)
			return (NULL);
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buf);
			return (line);
		}
		buf[read_byte] = '\0';
		line = ft_strjoin(line, buf);
		free(buf);
	}
	return (line);
}

char	*ft_get_line(char *buf, char *ret)
{
	size_t	i;
	size_t	len;

	i = 1;
	len = 1;
	if (!buf || buf[0] == '\0')
		return (NULL);
	while (buf[i - 1] != '\n' && buf[i])
	{
		len++;
		i++;
	}
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, buf, len + 1);
	return (ret);
}

int	get_next_line_second(char **save, char **line)
{
	char	*buf;
	char	*p;

	buf = NULL;
	buf = ft_strjoin(buf, *save + 1);
	*line = ft_get_line(buf, *line);
	p = ft_strchr(buf, '\n');
	free (*save);
	*save = NULL;
	if (p)
	{
		*save = ft_strjoin(*save, p);
		free(buf);
		return (1);
	}
	free(buf);
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	char		*p;
	static char	*save[OPEN_MAX];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	if (save[fd] && *save[fd] != '\0')
	{
		if (get_next_line_second(&save[fd], &line))
			return (line);
	}
	buf = ft_read_all(fd, line);
	if (!buf)
		return (NULL);
	line = ft_get_line(buf, line);
	p = ft_strchr(buf, '\n');
	if (p)
		save[fd] = ft_strjoin(save[fd], p);
	free(buf);
	return (line);
}
