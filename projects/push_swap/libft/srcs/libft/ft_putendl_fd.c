/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:09:22 by yaabdall          #+#    #+#             */
/*   Updated: 2024/09/08 23:12:37 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_putendl_fd function is used to write a string (*s)
to a file descriptor (fd). It appends a newline character.
*/
#include "../../includes/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = -1;
	while (s[++i])
		ft_putchar_fd(s[i], fd);
	ft_putchar_fd('\n', fd);
}
