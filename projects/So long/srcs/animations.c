/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:33:11 by aarmitan          #+#    #+#             */
/*   Updated: 2026/06/17 13:01:15 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

  void  animate_collectibles(t_game *game, long now)
  {
        int     prev;
        int     x;
        int     y;

        prev = game->blink_state;
        if (game->blink_state == 1 && now - game->last_blink >= 800)
        {
                game->blink_state = 0;
                game->last_blink = now;
        }
        else if (game->blink_state == 0 && now - game->last_blink >= 150)
        {
                game->blink_state = 1;
                game->last_blink = now;
        }
        if (prev == game->blink_state)
                return ;
        y = 0; 
        while (y < game->map_size.y)
        {
                x = 0;
                while (x < game->map_size.x)
                {
                        if (game->map[y][x] == 'C')
                        {
                                if (game->blink_state == 1)
                                        put_that_img(game->collec_img, x, y, game);
                                else
                                        put_that_img(game->bg_img, x, y, game);
                        }
                        x++;
                }
                y++;
        }
  }