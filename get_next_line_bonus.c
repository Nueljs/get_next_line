/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macerver <macerver@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:13:37 by macerver          #+#    #+#             */
/*   Updated: 2025/12/24 05:18:06 by macerver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill_remember(char *remember, char *buffer)
{
	if (!remember)
		remember = ft_strdup(buffer);
	else
		remember = ft_strjoin(remember, buffer);
	return (remember);
}

static char	*fill_and_read(char *remember, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytesread;
	
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
	if (remember[i] == '\n')
		i++;
	aux = ft_strdup(remember + i);
	free(remember);
	remember = aux;
	return (remember);
}

char	*get_next_line(int fd)
{
	static char *remember[1024];
	char	*line;
	
	line = NULL;
	if (!fd || fd < 0)
		return (NULL);
	remember[fd] = fill_and_read(remember[fd], fd);
	if (!remember[fd])
	{
		free(remember[fd]);
		remember[fd] = NULL;
		return (NULL);
	}
	line = fill_line(remember[fd], line);
	remember[fd] = handle_remember(remember[fd]);
	return (line);
}
