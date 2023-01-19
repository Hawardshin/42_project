/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:14:48 by joushin           #+#    #+#             */
/*   Updated: 2023/01/19 15:47:02 by joushin          ###   ########.fr       */
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
	if (data->y < 1)
		return ;
	if (data->map[data->y-1][data->x] != '0')
		return ;
	data->map[data->y][data->x] = '0';
	data->y--;
	data->map[data->y][data->x] = 'P';
	// img_set(*data);
}

void	move_s(t_game *data)
{
	if (data->y + 1 > data->high)
		return ;
	if (data->map[data->y+1][data->x] != '0')
		return ;
	data->map[data->y][data->x] = '0';
	data->y++;
	// data->map[data->y][data->x] = 'P';
	// img_set(*data);
}

void	move_a(t_game *data)
{
	if (data->x < 1)
		return ;
	if (data->map[data->y][data->x - 1] != '0')
		return ;
	data->map[data->y][data->x] = '0';
	data->x--;
	data->map[data->y][data->x] = 'P';
	// img_set(*data);
}

void	move_d(t_game *data)
{
	if (data->x > data->width)
		return ;
	if (data->map[data->y][data->x+1] != '0')
		return ;
	data->map[data->y][data->x] = '0';
	data->x++;
	// data->map[data->y][data->x] = 'P';
	// img_set(*data);
}


int	key_press(int keycode, t_game *param)
{
	if (keycode == KEY_W)
		move_w(param);
	else if (keycode == KEY_S)
		move_s(param);
	else if (keycode == KEY_A)
		move_a(param);
	else if (keycode == KEY_D)
		move_d(param);
	else if (keycode == KEY_ESC)
		exit_game(param);
	printf("x : %d y : %d\n", param->x, param->y);
	return (0);
}
