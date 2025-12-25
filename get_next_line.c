/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macerver <macerver@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:20:05 by macerver          #+#    #+#             */
/*   Updated: 2025/12/21 18:24:32 by macerver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line(char *remember)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!remember || *remember == '\0')
		return (NULL);
	while (remember[i] && remember[i] != '\n')
		i++;
	if (remember[i] == '\n')
		i++;
	line = ft_substr(remember, 0, i);
	return (line);
}

static char	*handle_remember(char *remember)
{
	int		i;
	char	*new;

	if (!remember)
		return (NULL);
	i = 0;
	while (remember[i] && remember[i] != '\n')
		i++;
	if (remember[i] == '\0')
	{
		free(remember);
		return (NULL);
	}
	i++;
	new = ft_strdup(remember + i);
	free(remember);
	if (!new || new[0] == '\0')
	{
		free(new);
		return (NULL);
	}
	return (new);
}

static char	*fill_remember(char *remember, char *buffer)
{
	char	*temp;

	if (!remember)
		remember = ft_strdup(buffer);
	else
	{
		temp = ft_strjoin(remember, buffer);
		free(remember);
		remember = temp;
	}
	return (remember);
}

static char	*read_and_fill(int fd, char *remember)
{
	ssize_t	bytesread;
	char	buffer[BUFFER_SIZE + 1];

	bytesread = 1;
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

char	*get_next_line(int fd)
{
	static char	*remember;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remember = read_and_fill(fd, remember);
	if (!remember || *remember == '\0')
	{
		free(remember);
		remember = NULL;
		return (NULL);
	}
	line = fill_line(remember);
	if (!line)
	{
		free(remember);
		remember = NULL;
		return (NULL);
	}
	remember = handle_remember(remember);
	return (line);
}


