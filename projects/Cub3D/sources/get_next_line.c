/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:19:34 by abastian          #+#    #+#             */
/*   Updated: 2025/07/11 17:25:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*line_analyse(int fd, char *buffer, char *stash)
{
	char	*temp;
	int		read_value;

	read_value = 1;
	while (read_value > 0)
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		if (read_value < 0)
		{
			if (stash)
				free(stash);
			return (NULL);
		}
		else if (read_value == 0)
			break ;
		if (!stash)
			stash = ft_strdup("");
		buffer[read_value] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*clean_stash_line(char *line)
{
	char	*stash;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0')
		return (NULL);
	stash = ft_substr(line, (i + 1), ft_strlen(line) - i + 1);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || read(fd, buffer, 0) < 0)
	{
		if (stash)
			free(stash);
		stash = NULL;
		free(buffer);
		return (NULL);
	}
	line = line_analyse(fd, buffer, stash);
	free(buffer);
	if (!line)
		return (NULL);
	stash = clean_stash_line(line);
	return (line);
}
