/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:59:13 by ilymegy           #+#    #+#             */
/*   Updated: 2023/08/17 22:25:55 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_len(const char *str)
{
	int	n;

	n = 0;
	while (str[n])
		++n;
	return (n);
}

int	is_newline(t_gnl *s)
{
	int		i;
	t_gnl	*curr;

	i = 0;
	if (!s)
		return (0);
	curr = get_last(s);
	while (curr->content[i])
	{
		if (curr->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_gnl	*get_last(t_gnl *str)
{
	t_gnl	*s;

	s = str;
	while (s && s->next)
		s = s->next;
	return (s);
}

void	create_line(t_gnl *str, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (str)
	{
		i = 0;
		while (str->content[i])
		{
			if (str->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		str = str->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (!(*line))
	{
		free_str(str);
		str = NULL;
	}
}

void	free_str(t_gnl *str)
{
	t_gnl	*s;
	t_gnl	*tmp;

	s = str;
	while (s)
	{
		free(s->content);
		tmp = s->next;
		free(s);
		s = tmp;
	}
}
