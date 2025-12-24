# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"

static void	print_and_free(char *line)
{
	if (!line)
	{
		printf("NULL\n");
		return ;
	}
	printf("%s", line);
	free(line);
}

static void	read_all(int fd, const char *label)
{
	char	*line;

	printf("--- %s ---\n", label);
	while ((line = get_next_line(fd)) != NULL)
		print_and_free(line);
	printf("(EOF -> ");
	line = get_next_line(fd);
	if (line == NULL)
		printf("NULL)\n");
	else
	{
		printf("NOT NULL)\n");
		print_and_free(line);
	}
}

int	main(void)
{
	int	fd;
	int	fd2;

	fd = open("text.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	if (fd < 0 || fd2 < 0)
	{
		perror("open");
		if (fd >= 0)
			close(fd);
		if (fd2 >= 0)
			close(fd2);
		return (1);
	}
	read_all(fd, "text.txt");
	read_all(fd2, "text2.txt");
	close(fd);
	close(fd2);
	return (0);
}