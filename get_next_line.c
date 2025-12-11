/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macerver <macerver@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:20:05 by macerver          #+#    #+#             */
/*   Updated: 2025/12/11 16:01:54 by macerver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	// static char	*remember;
	int			bytesread;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int	i;
	i = 0;

	bytesread = 0;
	bytesread = read(fd, buffer, BUFFER_SIZE);
	line = malloc (BUFFER_SIZE + 1);
	line[BUFFER_SIZE] = '\0';
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			break;
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

int	main()
{
	int	fd = open("text.txt", O_RDONLY);
	
	puts(get_next_line(fd));
	return 0;
}
