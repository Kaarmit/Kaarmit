/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:06:00 by aarmitan          #+#    #+#             */
/*   Updated: 2024/06/11 15:24:36 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <assert.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		ft_printstr(char *str, int *output);
int		ft_printchar(int c);
void	ft_print_id(int n, int *output);
void	ft_print_u(unsigned int value, int *output);
void	ft_print_ptr(unsigned long long n, int *output);
void	ft_print_hexa(unsigned int value, const char c, int *output);
void	ft_putchar_fd(char c, int fd);

#endif
