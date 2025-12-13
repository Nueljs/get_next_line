/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macerver <macerver@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:20:05 by macerver          #+#    #+#             */
/*   Updated: 2025/12/13 20:03:13 by macerver         ###   ########.fr       */
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
	return (line);
}

char	*handle_remember(char *remember, char *line)
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

char	*get_next_line(int fd)
{
	static char	*remember;
	int			bytesread;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;

	bytesread = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (NULL);
		buffer[bytesread] = '\0';
		if (!remember)
			remember = ft_strdup(buffer);
		else
			remember = ft_strjoin(remember, buffer);
		if (ft_strchr(remember, '\n'))
		{
			line = fill_line(remember);
			remember = handle_remember(remember, line);
		}
		return (line);
	}
	return (NULL);
}

int	main()
{
	int	fd = open("text.txt", O_RDONLY);
	
	puts(get_next_line(fd));
	puts(get_next_line(fd));
	puts(get_next_line(fd));
	puts(get_next_line(fd));
	puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	// puts(get_next_line(fd));
	return 0;
}
