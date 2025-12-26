/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macerver <macerver@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:13:37 by macerver          #+#    #+#             */
/*   Updated: 2025/12/26 05:19:27 by macerver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill_remember(char *remember, char *buffer)
{
	char	*temp;

	if (!remember)
		return (ft_strdup(buffer));
	temp = ft_strjoin(remember, buffer);
	free(remember);
	return (temp);
}

static char	*fill_and_read(char *remember, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytesread;

	while (!remember || !ft_strchr(remember, '\n'))
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == 0)
			break ;
		if (bytesread < 0)
		{
			free(remember);
			return (NULL);
		}
		buffer[bytesread] = '\0';
		remember = fill_remember(remember, buffer);
		if (!remember)
			return (NULL);
	}
	return (remember);
}

static char	*fill_line(char *remember, char *line)
{
	int	i;

	i = 0;
	while (remember[i] && remember[i] != '\n')
		i++;
	if (remember[i] == '\n')
		i++;
	line = ft_substr(remember, 0, i);
	return (line);
}

static char	*handle_remember(char *remember)
{
	char	*aux;
	int		i;

	i = 0;
	while (remember[i] && remember[i] != '\n')
		i++;
	if (remember[i] == '\0')
	{
		free(remember);
		return (NULL);
	}
	i++;
	aux = ft_strdup(remember + i);
	free(remember);
	if (!aux || aux[0] == '\0')
	{
		free(aux);
		return (NULL);
	}
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*remember[1024];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	remember[fd] = fill_and_read(remember[fd], fd);
	if (!remember[fd] || remember[fd][0] == '\0')
	{
		free(remember[fd]);
		remember[fd] = NULL;
		return (NULL);
	}
	line = fill_line(remember[fd], line);
	if (!line)
	{
		free(remember[fd]);
		remember[fd] = NULL;
		return (NULL);
	}
	remember[fd] = handle_remember(remember[fd]);
	return (line);
}
