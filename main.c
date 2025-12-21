# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"

int	main()
{
	int	fd = open("text.txt", O_RDONLY);
	int	fd2 = open("text2.txt", O_RDONLY);

	char *line;
	char *l_2text;

	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// }
	
	// printf("%s\n", get_next_line(fd));
	
	// while ((l_2text = get_next_line(fd2)) != NULL)
	// {
	// 	printf("%s", l_2text);
	// 	free(l_2text);
	// }
	
	// printf("%s", get_next_line(fd2));
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);

	line = get_next_line(fd2);
	printf("%s\n", line);
	free(line);


	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);

	line = get_next_line(fd2);
	printf("%s\n", line);
	free(line);

	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	
	line = get_next_line(fd2);
	printf("%s\n", line);
	free(line);

	return 0;
}