/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:25:54 by tson              #+#    #+#             */
/*   Updated: 2023/01/21 20:54:22 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

int	on_keyboard_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit(0);
	else if (keycode == W)
		move_vertical(game, FORWARD);
	else if (keycode == S)
		move_vertical(game, BACKWARD);
	else if (keycode == A)
		move_horizontal(game, LEFT);
	else if (keycode == D)
		move_horizontal(game, RIGHT);
	else if (keycode == LEFT_ARROW)
		rotate(game, LEFT);
	else if (keycode == RIGHT_ARROW)
		rotate(game, RIGHT);
	return (0);
}

void	move_vertical(t_game *game, t_axis axis)
{
	int	x;
	int	y;

	x = (int)(game->p_info.pos.x - game->p_info.dir.x * MOVE_SPEED * axis);
	y = (int)(game->p_info.pos.y + game->p_info.dir.y * MOVE_SPEED * axis);
	if (game->map[(int)(game->p_info.pos.y)][x] == '0')
		game->p_info.pos.x -= game->p_info.dir.x * MOVE_SPEED * axis;
	if (game->map[y][(int)(game->p_info.pos.x)] == '0')
		game->p_info.pos.y += game->p_info.dir.y * MOVE_SPEED * axis;
}

void	move_horizontal(t_game *game, t_axis axis)
{
	int			x;
	int			y;
	t_vector	dir;

	dir.x = game->p_info.dir.x * cos(M_PI / 2)
		- game->p_info.dir.y * sin(M_PI / 2);
	dir.y = game->p_info.dir.x * sin(M_PI / 2)
		+ game->p_info.dir.y * cos(M_PI / 2);
	x = (int)(game->p_info.pos.x - dir.x * MOVE_SPEED * axis);
	y = (int)(game->p_info.pos.y + dir.y * MOVE_SPEED * axis);
	if (game->map[(int)(game->p_info.pos.y)][x] == '0')
		game->p_info.pos.x -= dir.x * MOVE_SPEED * axis;
	if (game->map[y][(int)(game->p_info.pos.x)] == '0')
		game->p_info.pos.y += dir.y * MOVE_SPEED * axis;
}

void	rotate(t_game *game, t_axis axis)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->p_info.dir.x;
	game->p_info.dir.x = game->p_info.dir.x * cos(ROT_SPEED * axis)
		- game->p_info.dir.y * sin(ROT_SPEED * axis);
	game->p_info.dir.y = old_dir_x * sin(ROT_SPEED * axis)
		+ game->p_info.dir.y * cos(ROT_SPEED * axis);
	old_plane_x = game->p_info.plane.x;
	game->p_info.plane.x = game->p_info.plane.x * cos(ROT_SPEED * axis)
		- game->p_info.plane.y * sin(ROT_SPEED * axis);
	game->p_info.plane.y = old_plane_x * sin(ROT_SPEED * axis)
		+ game->p_info.plane.y * cos(ROT_SPEED * axis);
}
