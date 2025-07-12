/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:40:50 by ilymegy           #+#    #+#             */
/*   Updated: 2024/09/12 12:56:15 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1[i] && s2[i])
	{
		while (s1[i] && s2[i])
		{
			if (s1[i] - s2[i])
				return (s1[i] - s2[i]);
			++i;
		}
		return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}
