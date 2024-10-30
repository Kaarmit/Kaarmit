/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabdall <yaabdall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:48:13 by yaabdall          #+#    #+#             */
/*   Updated: 2024/09/10 17:22:27 by yaabdall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

// GET_NEXT_LINE
char	*get_next_line(int fd);
char	*ft_extract_line(char **store, char **temp);
void	ft_read_line(int fd, char **store, char **temp, int read_count);
char	*ft_remaining_text(const char *s);

// HELPER
int		ft_newline(const char *s);
char	*ft_strdup(const char *s1);
void	ft_free(char **s);

#endif