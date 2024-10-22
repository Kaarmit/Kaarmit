/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrnbr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:46 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/22 17:27:38 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

void	ft_putstrnbr_fd(char *str, int nbr)
{
	ft_putstr_fd(str, 1);
	ft_putnbr_fd(nbr, 1);
	ft_putchar_fd('\n', 1);
}
