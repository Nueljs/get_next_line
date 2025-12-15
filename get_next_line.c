/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macerver <macerver@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:20:05 by macerver          #+#    #+#             */
/*   Updated: 2025/12/15 06:07:25 by macerver         ###   ########.fr       */
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

static char	*handle_remember(char *remember, char *line)
{
	int	i;
	int	len_rem;

	i = 0;
	while (remember[i] && remember[i] != '\n')
		i++;
	i++;
	len_rem = ft_strlen(remember) - ft_strlen(line);
	remember = ft_substr(remember, i, len_rem);
	return (remember);
}

static char *fill_remember(char *remember, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytesread;
	
	bytesread = 1;
	while (!ft_strchr(remember,'\n'))
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (NULL);
		buffer[bytesread] = '\0';
		if(!remember)
			remember = ft_strdup(buffer);
		else
			remember = ft_strjoin(remember, buffer);
	}
	return (remember);
}
static char	*first_time_read(char *remember, int fd)
{
	int	bytesread;
	char	buffer[BUFFER_SIZE + 1];
	
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread < 0)
		return (NULL);
	buffer[bytesread] = '\0';
	remember = ft_strdup(buffer);
	return (remember);
}

char	*get_next_line(int fd)
{
	static char	*remember;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remember)
		remember = first_time_read(remember, fd);
	if (ft_strchr(remember, '\n') || !fill_remember(remember, fd))
	{
		line = fill_line(remember);
		if (!line)
			return (NULL);
		remember = handle_remember(remember, line);
		return (line);
	}
	else if (!ft_strchr(remember, '\n'))
	{
		remember = fill_remember(remember, fd);
		line = fill_line(remember);
		remember = handle_remember(remember, line);
		return (line);
	}	
	return (NULL);
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
