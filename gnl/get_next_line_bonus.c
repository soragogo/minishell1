/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayu <mayu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 02:40:41 by mayyamad          #+#    #+#             */
/*   Updated: 2023/10/03 16:13:15 by mayu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_all(int fd, char *line)
{
	ssize_t	read_byte;
	char	*buf;

	read_byte = 1;
	while (!(ft_strchr_gnl(line, '\n')) && read_byte != 0)
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
		line = ft_strjoin_gnl(line, buf);
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
	ft_strlcpy_gnl(ret, buf, len + 1);
	return (ret);
}

int	get_next_line_second(char **save, char **line)
{
	char	*buf;
	char	*p;

	buf = NULL;
	buf = ft_strjoin_gnl(buf, *save + 1);
	*line = ft_get_line(buf, *line);
	p = ft_strchr_gnl(buf, '\n');
	free (*save);
	*save = NULL;
	if (p)
	{
		*save = ft_strjoin_gnl(*save, p);
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
	p = ft_strchr_gnl(buf, '\n');
	if (p)
		save[fd] = ft_strjoin_gnl(save[fd], p);
	free(buf);
	return (line);
}

// #include "get_next_line_bonus.h"
// #include <fcntl.h>
// #include <stdio.h>

// int main(int argc, char **argv)
// {
//     int fd;
//     char *line;

//     if (argc != 2)
//     {
//         printf("Usage: %s <filename>\n", argv[0]);
//         return (1);
//     }

//     fd = open(argv[1], O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("Line read: %s\n", line);
//         free(line);
//     }

//     close(fd);
//     return (0);
// }
