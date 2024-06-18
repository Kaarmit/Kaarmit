#include "get_next_line_bonus.h"

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

// #include "get_next_line.h"

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("fichier.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	close(fd);
// 	return (0);
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("fichier.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	close(fd);
// 	return (0);
// }


// # include <fcntl.h>

// int main(void) {
// 	int fd = open ("fichier.txt", O_RDONLY);
// 	char *line = get_next_line(-1);
// 	if (line == NULL)
// 		printf("null\n");
// 	else {
// 		printf("%s", line);
// 		free(line);
// 	}
// 	line = get_next_line(fd);
// 	if (line == NULL)
// 		printf("null\n");
// 	else {
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return 0;
// }
