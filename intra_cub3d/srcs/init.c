/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:48:21 by tson              #+#    #+#             */
/*   Updated: 2023/01/22 18:14:45 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "MY");
	game->screen.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->screen.data = (int *)mlx_get_data_addr(game->screen.img, &game->screen.bpp, &game->screen.size_line, &game->screen.endian);
	game->identifiers[NORTH] = ft_strdup(NO_ID);
	game->identifiers[SOUTH] = ft_strdup(SO_ID);
	game->identifiers[WEST] = ft_strdup(WE_ID);
	game->identifiers[EAST] = ft_strdup(EA_ID);
	game->identifiers[F_ID_IDX] = ft_strdup(F_ID);
	game->identifiers[C_ID_IDX] = ft_strdup(C_ID);
	// ft_strdup NULL guard

	game->colors[FLOOR] = COLOR_NOT_SET;
	game->colors[CEILING] = COLOR_NOT_SET;
	game->textures[0].img = NULL;
	game->textures[1].img = NULL;
	game->textures[2].img = NULL;
	game->textures[3].img = NULL;
}
