/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:16:52 by aarmitan          #+#    #+#             */
/*   Updated: 2024/09/12 11:51:51 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <mlx.h>

char	*ft_join_strings(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	unsigned int	i;
	char			*ptr;

	if (!s1)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1_len-- != 0)
		ptr[i++] = *s1++;
	while (s2_len-- != 0)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

void	put_text(t_game *game)
{
	char	*text;
	char	*number;

	number = ft_itoa(game->moves);
	text = ft_join_strings("Move: ", number);
	put_that_img(game->wall_img, 0, 0, game);
	put_that_img(game->wall_img, 1, 0, game);
	mlx_string_put(game->mlx_ptr, game->mlx_win, 5, 10, 0xff0000, text);
	ft_printf("moves : %d\n", game->moves);
	free(text);
	free(number);
}
