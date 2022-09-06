/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:31:47 by joushin           #+#    #+#             */
/*   Updated: 2022/09/06 20:54:16 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"
#include "./libft/libft.h"

void	move_w(t_param *param, t_game *data)
{
	if (param->y + 1 >= data->high || \
	data->map[(param->y + 1) * data->width + param->x] != '0')
		return ;
	data->map[param->y * data->width + param->x] = '0';
	param->y++;
	data->map[param->y * data->width + param->x] = 'P';
	img_set(*data);
}

void	move_s(t_param *param, t_game *data)
{
	if (param->y <= 1 || \
	data->map[(param->y - 1) * data->width + param->x] != '0')
		return ;
	data->map[param->y * data->width + param->x] = '0';
	param->y--;
	data->map[param->y * data->width + param->x] = 'P';
	img_set(*data);
}

void	move_a(t_param *param, t_game *data)
{
	if (param->x <= 1 || \
	data->map[param->y * data->width + (param->x -1)] != '0')
		return ;
	data->map[param->y * data->width + param->x] = '0';
	param->x--;
	data->map[param->y * data->width + param->x + 1] = 'P';
	img_set(*data);
}

void	move_d(t_param *param, t_game *data)
{
	if (param->x + 1 >= data->width || \
	data->map[param->y * data->width + (param->x + 1)] != '0')
		return ;
	data->map[param->y * data->width + param->x] = '0';
	param->x++;
	data->map[param->y * data->width + param->x] = 'P';
}

void	exit_game(t_param *param, t_game *data)
{
	param->x = -1;
	param->y = -1;
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
