/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:31:47 by joushin           #+#    #+#             */
/*   Updated: 2022/09/08 18:34:47 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"
#include "./libft/libft.h"

void	move_w(t_game *data)
{
	if (data->y < 1)
		return ;
	if (data->map[(data->y - 1) * data->width + data->x] == 'E' && data->flag)
		exit_game(data);
	if (data->map[(data->y - 1) * data->width + data->x] == 'c')
		data->map[(data->y - 1) * data->width + data->x] = '0';
	if (data->map[(data->y - 1) * data->width + data->x] == 'C' )
	{
		data->map[(data->y - 1) * data->width + data->x] = 'c';
		data->flag = 1;
		img_set(*data);
		return ;
	}
	if (data->map[(data->y - 1) * data->width + data->x] != '0')
		return ;
	data->map[data->y * data->width + data->x] = '0';
	data->y--;
	data->map[data->y * data->width + data->x] = 'P';
	img_set(*data);
}

void	move_s(t_game *data)
{
	if (data->y + 1 > data->high)
		return ;
	if (data->map[(data->y + 1) * data->width + data->x] == 'E' && data->flag)
		exit_game(data);
	if (data->map[(data->y + 1) * data->width + data->x] == 'c')
		data->map[(data->y + 1) * data->width + data->x] = '0';
	if (data->map[(data->y + 1) * data->width + data->x] == 'C')
	{
		data->map[(data->y + 1) * data->width + data->x] = 'c';
		data->flag = 1;
		img_set(*data);
		return ;
	}
	if (data->map[(data->y + 1) * data->width + data->x] != '0')
		return ;
	data->map[data->y * data->width + data->x] = '0';
	data->y++;
	data->map[data->y * data->width + data->x] = 'P';
	img_set(*data);
}

void	move_a(t_game *data)
{
	if (data->x < 1)
		return ;
	if (data->map[data->y * data->width + (data->x - 1)] == 'E' && data->flag)
		exit_game(data);
	if (data->map[data->y * data->width + (data->x - 1)] == 'c')
		data->map[data->y * data->width + (data->x - 1)] = '0';
	if (data->map[data->y * data->width + (data->x - 1)] == 'C')
	{
		data->map[data->y * data->width + (data->x - 1)] = 'c';
		data->flag = 1;
		img_set(*data);
		return ;
	}
	if (data->map[data->y * data->width + (data->x - 1)] != '0')
		return ;
	data->map[data->y * data->width + data->x] = '0';
	data->x--;
	data->map[data->y * data->width + data->x] = 'P';
	img_set(*data);
}

void	move_d(t_game *data)
{
	if (data->x > data->width)
		return ;
	if (data->map[data->y * data->width + (data->x + 1)] == 'E' && data->flag)
		exit_game(data);
	if (data->map[data->y * data->width + (data->x + 1)] == 'c')
		data->map[data->y * data->width + (data->x + 1)] = '0';
	if (data->map[data->y * data->width + (data->x + 1)] == 'C')
	{
		data->map[data->y * data->width + (data->x + 1)] = 'c';
		data->flag = 1;
		img_set(*data);
		return ;
	}
	if (data->map[data->y * data->width + (data->x + 1)] != '0')
		return ;
	data->map[data->y * data->width + data->x] = '0';
	data->x++;
	data->map[data->y * data->width + data->x] = 'P';
	img_set(*data);
}

int	exit_game(t_game *data)
{
	data->x = -1;
	data->y = -1;
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
