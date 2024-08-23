/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:48:37 by aarmitan          #+#    #+#             */
/*   Updated: 2024/08/23 15:49:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
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
