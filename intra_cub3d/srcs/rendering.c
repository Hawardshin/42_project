/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:50:29 by tson              #+#    #+#             */
/*   Updated: 2023/01/22 18:20:22 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	render(t_game *game)
{
	int			i;
	t_hit_point	hit_point;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		hit_point.ray = calculate_ray(game, i);
		dda(game, &hit_point);
		hit_point.perp_dist = calculate_perp_dist(game, hit_point);
		draw_one_line(game, hit_point,
			i, (int)(SCREEN_HEIGHT / hit_point.perp_dist));
		i++;
	}
}

void	draw_one_line(t_game *game, t_hit_point hit_point, int col, int length)
{
	t_rendering	ren;

	set_start_end(&ren, length);
	set_tex_idx(&ren, hit_point);
	set_tex_x(game, &ren, hit_point);
	draw_ceiling(game, ren, col);
	draw_texture(game, ren, col, length);
	draw_floor(game, ren, col);
}

void	draw_texture(t_game *game, t_rendering ren, int col, int length)
{
	int		i;
	int		tex_y;
	int		tex_h;
	int		color;

	ren.step = 1.0 * game->textures[ren.tex_idx].height / length;
	ren.tex_pos = (ren.draw_start - SCREEN_HEIGHT / 2 + length / 2) * ren.step;
	tex_h = game->textures[ren.tex_idx].height;
	i = ren.draw_start;
	while (i < ren.draw_end)
	{
		tex_y = (int)ren.tex_pos & (game->textures[ren.tex_idx].height - 1);
		ren.tex_pos += ren.step;
		color = game->textures[ren.tex_idx].data[tex_h * tex_y + ren.tex_x];
		game->screen.data[i * SCREEN_WIDTH + col] = color;
		i++;
	}
}

void	draw_ceiling(t_game *game, t_rendering ren, int col)
{
	int	i;

	i = 0;
	while (i < ren.draw_start)
	{
		game->screen.data[i * SCREEN_WIDTH + col] = game->colors[CEILING];
		i++;
	}
}

void	draw_floor(t_game *game, t_rendering ren, int col)
{
	int	i;

	i = ren.draw_end;
	(void)game;
	(void)col;
	while (i < SCREEN_HEIGHT - 1)
	{
		game->screen.data[i * SCREEN_WIDTH + col] = game->colors[FLOOR];
		i++;
	}
}
