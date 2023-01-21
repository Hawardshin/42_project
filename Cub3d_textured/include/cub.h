/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:02:20 by joushin           #+#    #+#             */
/*   Updated: 2023/01/21 15:02:32 by joushin          ###   ########.fr       */
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
// #define WINDOW_WIDTH 64
// #define WINDOW_HEIGHT 64

# define RGB_Red 0xFF0000
# define RGB_Green 0x00FF00
# define RGB_Blue 0x0000FF
# define RGB_White 0xFFFFFF
# define RGB_Yellow 0xFFF000
# define RGB_BLACK 0x000000

# define ROTATE_SPEED 0.05
# define MOVE_SPEED 0.05

# define XPM_WIDTH 64
# define XPM_HEIGHT 64

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
	t_img	no_img;
	t_img	so_img;
	t_img	ea_img;
	t_img	we_img;

	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	// void	*n_wall;
	// void	*s_wall;
	// void	*e_wall;
	// void	*w_wall;
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
	//화면에 넣을 데이터
	t_fdata asset;
}t_game;

typedef enum e_map_type
{
	PLAYER,
	WALL,
	EMPTY,
	ERROR,
}t_map_type;

typedef enum e_wall_type
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	LINE,
}t_wall_type;

typedef struct s_draw_vec
{
	//(즉 우리가 쏘는 레이저가 카메라 평면에서 어디에 있는지)
	// -1부터 1이다.
	double cameraX;
	//광선의 방향벡터
	//광선의 방향은 ( 방향벡터 ) + ( 카메라평면 x 배수 )
	double rayDirX;
	double rayDirY;
	//현재 지도에서 내가 위치한 위치벡터 game->x가 2.9라면 mapX = 2, -2.94라면 -2 즉 아랫자리 버림
	int mapX;
	int mapY;
	//그려야 할 길이
	int lineHeight;
	//세로 줄 그리기 시작하는 좌표 점
	int drawStart;
	//그리기 끝내는점
	int drawEnd;
	//실제로 벽에 부딪힌 x좌표를 정확하게 표시
	//다만 세로벽에 부딪혔다면, Y좌표이다.
	double wallX;
	//이제 우리는 벽에 텍스처표현을 해주기 위해 텍스처의 어떤 x좌표 texX 를 적용해야 하는지 알아냈습니다.
	//코드의 마지막 부분에서 wallX 로, 텍스처의 x좌표를 나타내는 texX 를 계산해 주었습니다.
	int texX;
	//스크린 픽셀에 따라서 한번에 얼마만큼 이동할지를 결정하는 step변수
	double step;
	//일단 텍스쳐의 위치 첫 시작점을 윈도우 크기에 맞춰서 첫 시작점을 정해준다.
	double texPos;
}t_draw_vec;

typedef struct s_dda_vec
{
	//현 위치에서 다음 x칸 이동할 때 대각선 길이
	//현 위치에서 다음 y칸 	이동할 때 대각선 길이
	double sideDistX;
	double sideDistY;
	//x한칸 이동할 때 대각선 길이
	//y한칸 이동할 때 대각선 길이
	double deltaDistX;
	double deltaDistY;
	//광선의 벽까지의 길이
	double perpWallDist;

	// x로 갈지 Y로 갈지 정한다.
	// 즉 얼마만큼 한번에 이동할지 x한걸음 y한걸음 정도로 이해
	// -1이나 1로 정한다.
	int stepX;
	int stepY;

	int hit; //벽에 부딛혔는지 확인한다.//루프의 종료조건
	int side; // 만약 세로줄에 부딪혔다면 side는 0 가로줄에 부딪혔다면 side = 1 입니다.

}t_dda_vec;


t_map_type check_type(char a);

void	error_handle(char *s);
char	*ft_strjoin_no_nl(char *dest, char *src);
char	*ft_strdup_no_nl(char *str);
// void 	draw_lines(t_game *game);
// void	draw_rectangles(t_game *game);
void	ray_casting(t_game *game);
int	key_press(int keycode, t_game *param);
int	exit_game(t_game *data);
void	parse_image_rgb(void *mlx, t_game *data);
// int	rotate_right(t_game *data);
// int	rotate_left(t_game *data);
// int	move_s(t_game *data);
// int	move_w(t_game *data);

#endif
