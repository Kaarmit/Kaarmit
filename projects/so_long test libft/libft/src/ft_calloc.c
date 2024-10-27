/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:15:02 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/02 13:15:04 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*call;

	if (count == 18446744073709551615UL || size == 18446744073709551615UL)
		return (NULL);
	call = malloc(count * size);
	if (!call)
		return (0);
	ft_bzero(call, count * size);
	return (call);
}
