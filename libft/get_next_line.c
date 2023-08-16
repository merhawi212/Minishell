/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:56:03 by mkiflema          #+#    #+#             */
/*   Updated: 2023/07/21 14:28:00 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_join(char *saved, char *buff)
{
	char	*joined_str;
	int		i;
	int		j;

	if (!saved)
	{
		saved = (char *)malloc(1 * sizeof(char));
		saved[0] = '\0';
	}
	j = ft_strlen(saved) + ft_strlen(buff);
	joined_str = (char *)malloc((j + 1) * sizeof(char));
	if (!joined_str)
		return (0);
	i = -1;
	j = 0;
	if (saved)
		while (saved[++i] != '\0')
			joined_str[i] = saved[i];
	while (buff[j])
		joined_str[i++] = buff[j++];
	joined_str[i] = '\0';
	free(saved);
	return (joined_str);
}

static char	*get_line(char *saved)
{
	char	*line;
	int		i;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] != '\n' && saved[i])
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] != '\n' && saved[i])
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		line[i] = '\0';
	}
	return (line);
}

static char	*get_next(char *saved)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (saved[i] != '\n' && saved[i])
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	next = malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		next[j++] = saved[i++];
	next[j] = '\0';
	free(saved);
	return (next);
}

static char	*read_and_add(int fd, char *saved)
{
	char	*buff;
	int		readed_bytes;

	buff = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed_bytes = 1;
	while (!(ft_strchr(saved, '\n')) && readed_bytes > 0)
	{
		readed_bytes = read(fd, buff, BUFFER_SIZE);
		if (readed_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[readed_bytes] = '\0';
		saved = str_join(saved, buff);
	}
	free(buff);
	return (saved);
}

void	*get_next_line(int fd, char **result)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (0);
	saved = read_and_add(fd, saved);
	if (!saved)
		return (0);
	line = get_line(saved);
	saved = get_next(saved);
	*result = line;
	return (line);
}
