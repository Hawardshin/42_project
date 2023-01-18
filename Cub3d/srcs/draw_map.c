/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:42:25 by joushin           #+#    #+#             */
/*   Updated: 2023/01/18 18:38:17 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// DDA를 이용해 한줄씩 줄을 그리는 함수

int	coordination(t_game *game, double x, double y)
{
	return ((int)floor(y) * game->width * TILE_SIZE + (int)floor(x));
}

void	draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	//fabs는 부동 소수점 절댓값연산이다.
	//즉 abs에서 앞에 float abs같은 느낌쓰 math.h에 있음
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);// 더 큰값이 step이래
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->img.data[coordination(game,x1,y1)] = 0xb3b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}
//그리드를 나누는 함수
void 	draw_lines(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->width)
	{//가로줄 먼저 그리고
		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, game->high * TILE_SIZE);
		i++;
	}
	draw_line(game, game->width * TILE_SIZE - 1, 0, game->width * TILE_SIZE - 1, game->high * TILE_SIZE);
	//가로줄 끝
	j = 0;
	while (j < game->high)
	{
		draw_line(game, 0, j * TILE_SIZE, game->width * TILE_SIZE, j * TILE_SIZE);
		j++;
	}
	draw_line(game, 0, game->high * TILE_SIZE - 1, game->width * TILE_SIZE, game->high * TILE_SIZE - 1);
}
//사각형 색칠하는 함수
void	draw_rectangle(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			game->img.data[((y  + i) * (game->width * TILE_SIZE)) + x + j] = 0xFFFFFF;//0xFFFFFF
			j++;
		}
		i++;
	}
}

//tmp_x = (tmp->dir_x * cos(angle)) - (tmp->dir_y * sin(angle));
//	tmp->dir_y = (tmp->dir_x * sin(angle)) + (tmp->dir_y * cos(angle));
//	tmp->dir_x = tmp_x;

//각도에 따라서 방향벡터를 구하는 함수
// double	x_direct(t_game *game,double angle)
// {
// 	return (ROTATE_N * sin(angle * PI / 180) *game->dir_x - ROTATE_N * cos(angle * PI / 180) * game->dir_y);
// }

// double	y_direct(t_game *game,double angle)
// {
// 	return (2 * game->dir_y * ROTATE_N * sin(angle * PI / 180));
// }

//레이저 그리는 함수
void	draw_razer(t_game *game, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	//fabs는 부동 소수점 절댓값연산이다.
	//즉 abs에서 앞에 float abs같은 느낌쓰 math.h에 있음
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);// 더 큰값이 step이래
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->img.data[coordination(game,x1,y1)] = 0xb3b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}
void	rotate_vector(t_game * tmp, double angle)
{
	double tmp_x = (tmp->dir_x * cos(angle)) - (tmp->dir_y * sin(angle));
	tmp->dir_y = (tmp->dir_x * sin(angle)) + (tmp->dir_y * cos(angle));
	tmp->dir_x = tmp_x;
}
void	draw_razers(t_game *game, int x, int y)
{
	int	dir_x = game->dir_x;
	int	dir_y = game->dir_y;
	//레이저가 끝나는 점을 어떻게 할까?
	//일단
	// rotate_vector(game, 0);
	draw_razer(game,x,y,x + 60*dir_x, y + 60*dir_y);
	rotate_vector(game,  (PI / 180));
	// printf("%f",x_direct(game,45));
	// draw_razer(game,x,y,x + x_direct(game,45),y+ y_direct(game,45));
}

void	draw_player(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = TILE_SIZE/3;
	while (i < 2*(TILE_SIZE/3))
	{
		j = TILE_SIZE/3;
		while (j < 2*(TILE_SIZE/3))
		{
			game->img.data[((y  + i) * (game->width * TILE_SIZE)) + x + j] = 0xCD0000;//Red
			j++;
		}
		i++;
	}
	draw_razers(game,x + TILE_SIZE/2,y+ TILE_SIZE/2);
}

//모든 사각형을 색칠하는 함수
void	draw_rectangles(t_game *game)
{
	int		i;
	int		j;
	int		size;
	i = 0;
	while (i < game->high)
	{
		j = 0;
		if (game->map)
			size = ft_strlen(game->map[i]);
		while (j < size)
		{
			if (check_type(game->map[i][j]) == WALL)
				draw_rectangle(game, j, i);
			if (check_type(game->map[i][j])== PLAYER)
				draw_player(game,j,i);
			j++;
		}
		i++;
	}
}

