/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:02:20 by joushin           #+#    #+#             */
/*   Updated: 2023/01/19 22:21:40 by joushin          ###   ########.fr       */
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
# define ROTATE_N				0.3
# define PI						3.1415926

//1 의 경우 시야각 90도
//시야각을 나타내는데 작아질 수록 시야가 작아진다. 스크린 사이즈의 절반의 길이를 의미
//이건 시야각이 90도보단 작은 경우이다.
//정확히 계산하자면 FOV = 2 * atan(0.66/1.0)=66.8°로 1인칭 슈팅게임(fps)에 적합함
# define VIEW_ANGLE 0.66

//화면 비율 16: 9 비율 준수
# define WINDOW_MAGNI 100
# define WINDOW_HEIGHT (WINDOW_MAGNI * 9)
# define WINDOW_WIDTH  (WINDOW_MAGNI * 16)

# define RGB_Red 0xFF0000
# define RGB_Green 0x00FF00
# define RGB_Blue 0x0000FF
# define RGB_White 0xFFFFFF
# define RGB_Yellow 0xFFF000
# define RGB_BLACK 0x000000

# define ROTATE_SPEED 0.05
# define MOVE_SPEED 0.05

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}t_img;

typedef struct s_fdata
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	void	*n_wall;
	void	*s_wall;
	void	*e_wall;
	void	*w_wall;
} t_fdata;

// a = (변화상수 sin(각도 변수 * 파이 /180) ,
// a = ROTATE_N * sin(angle * PI / 180);
// b = 변화상수cos(각도변수 * 파이 /180))
// b = ROTATE_N * cos(angle * PI / 180);
// 방향벡터 구하는 법:
// dir_x = a *dir_x - b*dir_y
// dir_x = ROTATE_N * sin(angle * PI / 180) *dir_x - ROTATE_N * cos(angle * PI / 180) * dir_y
// dir_y = 2ay
// dir_y = 2 * dir_y * ROTATE_N * sin(angle * PI / 180)

typedef struct s_game
{
	void	*mlx;
	void	*win;
	// 현재 위치
	double	x;
	double	y;
	//현재 방향벡터
	double		dir_x;
	double		dir_y;
	//스크린의 방향벡터
	double		plane_x;
	double		plane_y;
	//지도의 높이
	int		high;
	//지도
	int		width;
	char	**map;
	// 화면에 찍을 이미지
	t_img img;
	t_fdata asset;
}t_game;



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
// void 	draw_lines(t_game *game);
// void	draw_rectangles(t_game *game);
void	ray_casting(t_game *game);
int	key_press(int keycode, t_game *param);
int	exit_game(t_game *data);

// int	rotate_right(t_game *data);
// int	rotate_left(t_game *data);
// int	move_s(t_game *data);
// int	move_w(t_game *data);

#endif
