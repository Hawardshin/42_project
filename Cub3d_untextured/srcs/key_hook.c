/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:14:48 by joushin           #+#    #+#             */
/*   Updated: 2023/01/19 19:40:32 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	exit_game(t_game *data)
{
	data->x = -1;
	data->y = -1;
	free(data->map);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

void	move_w(t_game *data)
{
	if (data->y < 0)
		return ;
	if(data->map[(int)data->y][(int)(data->x + data->dir_x * MOVE_SPEED)] == '0')
		data->x += data->dir_x * MOVE_SPEED;
	if(data->map[(int)(data->y + data->dir_y * MOVE_SPEED)][(int)data->x]== '0')
		data->y += data->dir_y * MOVE_SPEED;
}

void	move_s(t_game *data)
{
	if (data->y + 1 > data->high)
		return ;
	if(data->map[(int)(data->y)][(int)(data->x - data->dir_x * MOVE_SPEED)] == '0')
		data->x -= data->dir_x * MOVE_SPEED;
	if(data->map[(int)(data->y - data->dir_y * MOVE_SPEED)][(int)(data->x)] == '0')
		data->y -= data->dir_y * MOVE_SPEED;
}

void	move_a(t_game *data)
{
	if (data->x < 1)
		return ;
	if(data->map[(int)(data->y)][(int)(data->x - data->dir_x * MOVE_SPEED)] == '0')
		data->x -= data->dir_x * MOVE_SPEED;
	// if(data->map[(int)(data->y - data->dir_y * MOVE_SPEED)][(int)(data->x)] == '0')
	// 	data->y -= data->dir_y * MOVE_SPEED;
}

// void	move_d(t_game *data)
// {
// 	if (data->x > data->width)
// 		return ;
// 	if (data->map[data->y][data->x+1] != '0')
// 		return ;
// 	data->map[data->y][data->x] = '0';
// 	data->x++;
// 	// data->map[data->y][data->x] = 'P';
// 	// img_set(*data);
// }

void	rotate_left(t_game *data)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = data->dir_x;
	oldPlaneX = data->plane_x;
	data->dir_x = data->dir_x * cos(-ROTATE_SPEED) - data->dir_y * sin(-ROTATE_SPEED);
	data->dir_y = oldDirX * sin(-ROTATE_SPEED) + data->dir_y * cos(-ROTATE_SPEED);
	data->plane_x = data->plane_x * cos(-ROTATE_SPEED) - data->plane_y * sin(-ROTATE_SPEED);
	data->plane_y = oldPlaneX * sin(-ROTATE_SPEED) + data->plane_y * cos(-ROTATE_SPEED);
}

void	rotate_right(t_game *data)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = data->dir_x;
	oldPlaneX = data->plane_x;
	data->dir_x = data->dir_x * cos(ROTATE_SPEED) - data->dir_y * sin(ROTATE_SPEED);
	data->dir_y = oldDirX * sin(ROTATE_SPEED) + data->dir_y * cos(ROTATE_SPEED);
	data->plane_x = data->plane_x * cos(ROTATE_SPEED) - data->plane_y * sin(ROTATE_SPEED);
	data->plane_y = oldPlaneX * sin(ROTATE_SPEED) + data->plane_y * cos(ROTATE_SPEED);
}

int	key_press(int keycode, t_game *param)
{
	if (keycode == KEY_W)
		move_w(param);
	if (keycode == KEY_S)
		move_s(param);
	if (keycode == KEY_A)
		rotate_left(param);
	if (keycode == KEY_D)
		rotate_right(param);
	if (keycode == KEY_ESC)
		exit_game(param);
	printf("x : %f y : %f\n", param->x, param->y);
	return (0);
}
