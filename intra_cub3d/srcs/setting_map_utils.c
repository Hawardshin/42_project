/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:02:13 by joushin           #+#    #+#             */
/*   Updated: 2023/01/22 22:07:09 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	is_around_wall(t_game *g, int y, int x, t_move_arr ar)
{
	int	i;

	i = -1;
	if (y != g->map_high - 1 && g->map_wid[y] > g->map_wid[y + 1] \
		&& x >= g->map_wid[y + 1])
		error_handle("INVALID MAP FORMAT\n");
	while (++i < 4)
	{
		if (x == 0 || y == 0 || x == g->map_wid[y] -1 || y == g->map_high -1)
			error_handle("INVALID MAP FORMAT\n");
		if (x + ar.dx[i] < 0 || y + ar.dy[i] < 0 || \
		y + ar.dy[i] >= g->map_high || x + ar.dx[i] >= g->map_wid[y + ar.dy[i]])
			continue ;
		if (check_type(g->map[y + ar.dy[i]][x + ar.dx[i]]) == SPACE)
			error_handle("INVALID MAP FORMAT\n");
	}
}

void	dont_go(t_game *g, int y, int x, t_move_arr ar)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (x + ar.dx[i] < 0 || y + ar.dy[i] < 0 || \
		y + ar.dy[i] >= g->map_high || x + ar.dx[i] >= g->map_wid[y + ar.dy[i]])
			continue ;
		if (check_type(g->map[y + ar.dy[i]][x + ar.dx[i]]) == EMPTY)
			error_handle("INVALID MAP FORMAT\n");
	}
}

void	check_around_wall(t_game *g, t_move_arr ar)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->map_high)
	{
		j = 0;
		while (j < g->map_wid[i])
		{
			if (check_type(g->map[i][j]) == EMPTY)
				is_around_wall(g, i, j, ar);
			if (check_type(g->map[i][j]) == SPACE)
				dont_go(g, i, j, ar);
			if (check_type(g->map[i][j]) == PLAYER)
				is_around_wall(g, i, j, ar);
			j++;
		}
		i++;
	}
}

void	init_mapping(t_move_arr *arr, t_game *g)
{
	arr->dx[0] = 0;
	arr->dx[1] = -1;
	arr->dx[2] = 0;
	arr->dx[3] = 1;
	arr->dy[0] = 1;
	arr->dy[1] = 0;
	arr->dy[2] = -1;
	arr->dy[3] = 0;
	g->p_info.pos.x = -1;
	g->p_info.pos.y = -1;
	g->p_info.dir.x = 0;
	g->p_info.dir.y = 0;
	g->p_info.plane.x = 0;
	g->p_info.plane.y = 0;
}
