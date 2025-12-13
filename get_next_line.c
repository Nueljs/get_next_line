/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macerver <macerver@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:20:05 by macerver          #+#    #+#             */
/*   Updated: 2025/12/13 05:54:38 by macerver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line(char *remember)
{
	char	*line;
	size_t	i;
	size_t	len;
	
	i = 0;
	if (!remember)
		return (NULL);
	while (remember[i] && remember[i] != '\n')
		i++;
	line = ft_substr(remember, 0, i);
	len = ft_strlen(remember) - i;
	remember = ft_substr(remember, i, len);
	return (line);
}

char	*handle_remember(char *remember, char *buffer)
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
	int			bytesread;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;

	bytesread = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((bytesread = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (bytesread < 0)
			return (NULL);
		buffer[bytesread] = '\0';
		remember = handle_remember(remember, buffer);
		if (!remember)
			return (NULL);
		if (ft_strchr(remember, '\n'))
			line = fill_line(remember);
	}
		
	return (line);
}

int	main()
{
	int	fd = open("text.txt", O_RDONLY);
	
	puts(get_next_line(fd));
	puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	return 0;
}
