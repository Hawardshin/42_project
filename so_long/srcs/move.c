/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:31:47 by joushin           #+#    #+#             */
/*   Updated: 2022/09/08 16:03:27 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"
#include "./libft/libft.h"

void	move_w(t_game *data)
{
	if (data->y < 1 || \
	data->map[(data->y - 1) * data->width + data->x] != '0')
		return ;
	data->map[data->y * data->width + data->x] = '0';
	data->y--;
	data->map[data->y * data->width + data->x] = 'P';
	img_set(*data);
}

void	move_s(t_game *data)
{
	if (data->y + 1 > data->high || \
	data->map[(data->y + 1) * data->width + data->x] != '0')
		return ;
	data->map[data->y * data->width + data->x] = '0';
	data->y++;
	data->map[data->y * data->width + data->x] = 'P';
	img_set(*data);
}

void	move_a(t_game *data)
{
	if (data->x < 1 || \
	data->map[data->y * data->width + (data->x - 1)] != '0')
		return ;
	data->map[data->y * data->width + data->x] = '0';
	data->x--;
	data->map[data->y * data->width + data->x] = 'P';
	img_set(*data);
}

void	move_d(t_game *data)
{
	if (data->x > data->width || \
	data->map[data->y * data->width + (data->x + 1)] != '0')
		return ;
	data->map[data->y * data->width + data->x] = '0';
	data->x++;
	data->map[data->y * data->width + data->x] = 'P';
	img_set(*data);
}

void	exit_game(t_game *data)
{
	data->x = -1;
	data->y = -1;
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
