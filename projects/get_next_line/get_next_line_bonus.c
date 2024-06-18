/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:56:49 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/16 17:17:02 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	test(void)
{
	get_next_line(-42);
}

char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*set_line(char *line_buffer)
{
	size_t	i;
	char	*stash;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i])
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	stash = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - (i + 1));
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash[fd])
			free(stash[fd]);
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || read(fd, buffer, 0) < 0)
	{
		free(stash[fd]);
		free(buffer);
		stash[fd] = NULL;
		return (NULL);
	}
	line = fill_line_buffer(fd, stash[fd], buffer);
	free(buffer);
	if (!line)
		return (NULL);
	stash[fd] = set_line(line);
	return (line);
}
