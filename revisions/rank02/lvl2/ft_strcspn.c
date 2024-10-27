/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:29:06 by aarmitan          #+#    #+#             */
/*   Updated: 2024/10/15 16:32:06 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i = 0;
	int	j = 0;

	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if(s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
