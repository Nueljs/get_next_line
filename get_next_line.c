/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macerver <macerver@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:20:05 by macerver          #+#    #+#             */
/*   Updated: 2025/12/16 05:51:35 by macerver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line(char *remember)
{
	char	*line;
	size_t	i;
	size_t	len;

	i = 0;
	if (!remember || *remember == '\0')
		return (NULL);
	while (remember[i] && remember[i] != '\n')
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
	if (remember[i] == '\n')
		i++;
	new = ft_strdup(remember + i);
	free(remember);
	return (new);
}

static char *fill_remember(char *remember, char *buffer)
{
	if (!remember)
		remember = ft_strdup(buffer);
	else
		remember = ft_strjoin(remember, buffer);
	return (remember);
}

char	*get_next_line(int fd)
{
	static char	*remember;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	int			bytesread;

	bytesread = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!remember || !ft_strchr(remember, '\n') && bytesread != 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		buffer[bytesread] = '\0';
		if (bytesread == 0)
			break;
		if (bytesread < 0)
			return (NULL);
		if (bytesread > 0)
			remember = fill_remember(remember, buffer);
	}
	if (bytesread == 0 && (!remember || *remember == '\0'))
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

int	main()
{
	int	fd = open("text.txt", O_RDONLY);
	
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	return 0;
}
