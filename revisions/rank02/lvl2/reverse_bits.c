/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:25:47 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/17 12:28:17 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char 	reverse_bits(unsigned char octet)
{
	int	i = 8;
	unsigned char	res = 0;

	while (i > 0)
	{
		res = res * 2 + (octet % 2);
		octet = octet / 2;
		i--;
	}
	return (res);
}
