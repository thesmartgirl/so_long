#include "libft/libft.h"
#include <fcntl.h>

int	main(void)
{
	int i = 0;
	char *line;
	int fd = open("map.ber", O_RDONLY);

	while (1)
	{
		ft_printf("i = %d\n", i);
		line = get_next_line(fd);
		ft_printf("line = %s", line);
		ft_printf("line len = %d\n", ft_strlen(line));
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';

		// ft_printf("len = %d, line = %s\n", ft_strlen(line), line);
		free(line);
		i++;
	}
	close(fd);
}