/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:52:43 by tson              #+#    #+#             */
/*   Updated: 2023/01/22 21:09:23 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	set_start_end(t_rendering *ren, int length)
{
	ren->draw_start = -length / 2 + SCREEN_HEIGHT / 2;
	ren->draw_end = length / 2 + SCREEN_HEIGHT / 2;
	if (ren->draw_start < 0 || length < 0)
		ren->draw_start = 0;
	if (ren->draw_end >= SCREEN_HEIGHT || length < 0)
		ren->draw_end = SCREEN_HEIGHT - 1;
}

void	set_tex_idx(t_rendering *ren, t_hit_point hit_point)
{
	if (hit_point.is_hit_ns && hit_point.ray.y > 0)
		ren->tex_idx = SOUTH;
	else if (hit_point.is_hit_ns && hit_point.ray.y < 0)
		ren->tex_idx = NORTH;
	else if (!hit_point.is_hit_ns && hit_point.ray.x > 0)
		ren->tex_idx = WEST;
	else
		ren->tex_idx = EAST;
}

void	set_tex_x(t_game *game, t_rendering *ren, t_hit_point hit_point)
{
	double	wall_x;

	if (hit_point.is_hit_ns)
		wall_x = game->p_info.pos.x + hit_point.perp_dist * hit_point.ray.x;
	else
		wall_x = game->p_info.pos.y + hit_point.perp_dist * hit_point.ray.y;
	wall_x -= floor(wall_x);
	ren->tex_x = (int)(wall_x * (double)game->textures[ren->tex_idx].width);
	if (hit_point.is_hit_ns == FALSE && hit_point.ray.x > 0)
		ren->tex_x = game->textures[ren->tex_idx].width - ren->tex_x - 1;
	if (hit_point.is_hit_ns == TRUE && hit_point.ray.y < 0)
		ren->tex_x = game->textures[ren->tex_idx].width - ren->tex_x - 1;
}
