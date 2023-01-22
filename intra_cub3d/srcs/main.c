/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 14:09:39 by tson              #+#    #+#             */
/*   Updated: 2023/01/22 18:25:25 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

int	loop_function(t_game *game)
{
	render(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}

int	on_click_x_btn(void)
{
	exit(0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	init_game(&game);
	check_arg(argc, argv, &game);
	printf("floor : %d, ceiling : %d\n", game.colors[FLOOR], game.colors[CEILING]);
	mlx_hook(game.win, KEY_PRESS, 0, on_keyboard_press, &game);
	mlx_hook(game.win, KEY_EXIT, 0, on_click_x_btn, NULL);
	mlx_loop_hook(game.mlx, loop_function, &game);
	mlx_loop(game.mlx);
	return (0);
}
