/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:02:20 by joushin           #+#    #+#             */
/*   Updated: 2023/01/18 18:21:34 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../srcs/libft/libft.h"
# include "../mlx/mlx.h"
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
//변화 상수
# define ROTATE_N				1
# define PI						3.1415926

# define TILE_SIZE 64


typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	// 현재 위치
	int		x;
	int		y;
	//현재 방향벡터
	// a = (변화상수 sin(각도 변수 * 파이 /180) ,
	// a = ROTATE_N * sin(angle * PI / 180);
	// b = 변화상수cos(각도변수 * 파이 /180))
	// b = ROTATE_N * cos(angle * PI / 180);
	// 방향벡터 구하는 법:
	// dir_x = a *dir_x - b*dir_y
	// dir_x = ROTATE_N * sin(angle * PI / 180) *dir_x - ROTATE_N * cos(angle * PI / 180) * dir_y
	// dir_y = 2ay
	// dir_y = 2 * dir_y * ROTATE_N * sin(angle * PI / 180)
	double		dir_x;
	double		dir_y;
	//혹시 몰라서 현재 방향 각도 변수까지 줬다. 내가 이해하기 쉬우려고!
	double		angle;
	//지도의 높이
	int		high;
	//지도
	int		width;
	char	**map;
	// 찍을 이미지
	t_img img;
}t_game;



typedef struct s_fdata
{

	void	*wall;
	void	*land;
	void	*play;
	void	*chest;
	void	*chest_open;
	void	*out;
} t_fdata;


typedef enum e_map_type
{
	PLAYER,
	WALL,
	EMPTY,
	ERROR,
}t_map_type;

t_map_type check_type(char a);

void	error_handle(char *s);
char	*ft_strjoin_no_nl(char *dest, char *src);
char	*ft_strdup_no_nl(char *str);
void 	draw_lines(t_game *game);
void	draw_rectangles(t_game *game);
#endif
