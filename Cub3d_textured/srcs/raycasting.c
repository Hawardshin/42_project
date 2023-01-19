/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:43:54 by joushin           #+#    #+#             */
/*   Updated: 2023/01/19 22:10:10 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// draw_line(game, 0, j * TILE_SIZE, game->width * TILE_SIZE, j * TILE_SIZE);
void	draw_longitude_line(t_game *game, int image_idx, double start, double end, int color)
{

	while (start < end)
	{
		game->img.data[(int) (start * WINDOW_WIDTH +(image_idx))] = color;
		start++;
	}
}

void	ray_casting(t_game *game)
{
	int	line;

	line =0;
	//이번에는 이전에 스크린에 세로로 줄 하나씩 찍는 방법을 사용할 수 없다.
	// while (line < WINDOW_WIDTH)
	while (!done())
	{
		//루프 한번 당, 레이저 하나씩 쏴서 그 값을 이용해 거리를 보는것이다.

		//화면의 수직선의 위치가 카메라 평면에서 의 값
		//(즉 우리가 쏘는 레이저가 카메라 평면에서 어디에 있는지)
		// -1부터 1이다.
		/*
		for문의 x값이 0이면 (스크린의 왼쪽 끝이면) cameraX = -1
		for문의 x값이 w/2이면 (스크린의 중앙이면) cameraX = 0
		for문의 x값이 w이면 (스크린의 오른쪽 끝이면) cameraX = 1
		*/
		double cameraX = (2 * line) / ((double)WINDOW_WIDTH) -1;
		double rayDirX = game->dir_x + game->plane_x * cameraX;
		double rayDirY = game->dir_y + game->plane_y * cameraX;
		/*
		광선의 방향은 ( 방향벡터 ) + ( 카메라평면 x 배수 )
		*/
		//현재 지도에서 내가 위치한 위치벡터 game->x가 2.9라면 mapX = 2, -2.94라면 -2 즉 아랫자리 버림
		int mapX = (int)game->x;
		int mapY = (int)game->y;

		//--------------------DDA용 변수------------------//

		//현 위치에서 다음 x칸 이동할 때 대각선 길이
		//현 위치에서 다음 y칸 이동할 때 대각선 길이
		double sideDistX;
		double sideDistY;
		//x한칸 이동할 때 대각선 길이
		//y한칸 이동할 때 대각선 길이
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		//광선의 벽까지의 길이
		double perpWallDist;

		// x로 갈지 Y로 갈지 정한다.
		// 즉 얼마만큼 한번에 이동할지 x한걸음 y한걸음 정도로 이해
		// -1이나 1로 정한다.
		int stepX;
		int stepY;

		//
		int hit = 0; //벽에 부딛혔는지 확인한다.//루프의 종료조건
		int side; // 만약 세로줄에 부딪혔다면 side는 0 가로줄에 부딪혔다면 side = 1 입니다.
		//--------------------DDA용 변수------------------//
	//-------------------------DDA시작-------------------//

	if (rayDirX < 0)//광선의 방향벡터중 x가 음수일때
	{ // sideDistX rayDirX 의 값이 음수 일 경우 광선의 시작점부터 왼쪽 으로 이동하다 처음 만나는 x면까지의 거리
		stepX = -1;
		sideDistX = (game->x - mapX) * deltaDistX; //game->x - mapX (이건 버린 소수점을 의미)
	}
	else
	{//sideDistX 의 값은, rayDirX 의 값이 양수 일 경우, '광선의 시작점부터 오른쪽 으로 이동하다 처음 만나는 x면까지의 거리'입니다.
		stepX = 1;
		sideDistX = (mapX + 1.0 - game->x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (game->y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - game->y) * deltaDistY;
	}
	//DDA를 합니다.
	while (hit == 0)
	{//벽에 부딪힐 때까지 광선을 한칸씩 앞으로 이동시키는 루프
		if (sideDistX < sideDistY) //왼쪽으로 한칸 갈 때
		{
			sideDistX += deltaDistX;//현재까지 빛이 X한칸 이동할 때 거리를 갱신
			mapX += stepX;//X 방향으로 한칸 이동
			side = 0; // 세로줄에 부딪힌 상황
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;//Y  방향으로 한칸 이동
			side = 1;//가로줄에 부딪힌 상황
		}
		//벽에 부딪히면 hit를 0으로 바꿔줍니다.
		//이 때, 변수 side 의 값이 0이면 벽의 x면에, 1이면 벽의 y면에 부딪혔다는 것을 알 수 있고,
		//또 mapX, mapY 로 어떤 벽이랑 부딪힌 건지도 알 수 있습니다.
		//다만 정확히 벽에 어떤 지점에 부딪혔는지는 모른다.
		//하지만 아직 텍스쳐를 안 하기 떄문에 괜찮다.
		if (game->map[mapY][mapX] == '1') hit = 1;
	}
	//벽을 만나서 DDA가 왼료되었으니..! 이제 시작점에서 벽까지 이동거리를 계산한다.
	//이 거리는 나중에 벽을 얼마나 높게 그릴지 알아내는데 사용됩니다.
	//어안렌즈 효과 (fisheye effect) 는 실제 거리 값을 사용했을 때 모든 벽이 둥글게 보여서 회전할 때 울렁거릴 수도 있는 현상을 말합니다.
	//이러한 어안렌즈 효과 를 피하기 위해, 플레이어 위치까지의 유클리드 거리 대신에, 카메라 평면까지의 거리 (또는 카메라 쪽으로 플레이어에 투사된 지점의 거리)를 사용할 것입니다.

	//이 레이저가 부딪힌 장애물에서 수직거리를 의미합니다.
	//만약 광선의 방향이 x면에 수직이면 이미 정확한 수직거리의 값이지만 대부분의 경우 광선의 방향이 있고 이 때 구해진 값은 실제 수직거리보다 큰 값이므로 rayDirX 로 나누어줍니다.
	//y면에 부딪힌 경우에도 같은 방식으로 계산해줍니다.
	//mapX - posX 가 음수이더라도 역시 음수인 rayDirX 로 나누어 계산된 값은 항상 양수가 됩니다.
	if (side == 0)//만약 광선이 처음으로 부딪힌 면이 세로선이라면, mapX - posX + (1 - stepX) / 2) 는 광선이 x방향으로 몇 칸이나 지나갔는지를 나타내는 수입니다
		perpWallDist = (mapX - game->x + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - game->y + (1 - stepY) / 2) / rayDirY;
	//Calculate height of line to draw on screen

	//perpWallDist 를 역수로 취하고, 픽셀단위로 맞춰주기 위해 픽셀 단위의 화면높이 h 를 곱해서 구할 수 있습니다.
	////즉 쉽게 말해서, 그냥 벽의 높이를 더 크게 하고싶으면 더 크게 해도 된다.
	//lineHeight (화면에 그려야 할 수직선의 높이)에서, 실제로 선을 그릴 위치의 시작 및 끝 위치를 알 수 있습니다.
	int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

	int drawStart = (int)(-lineHeight / 2 + (WINDOW_HEIGHT) / 2);
	if(drawStart < 0)
		drawStart = 0;
	//벽의 중심은 화면의 중심에 있어야 하고, 이 중심점이 화면 범위 아래에 놓여있다면 0 으로, 화면 범위 위에 놓여있다면 h-1으로 덮어씌웁니다.
	int drawEnd = lineHeight / 2 + (WINDOW_HEIGHT) / 2;
	if(drawEnd >= WINDOW_HEIGHT)
		drawEnd = WINDOW_HEIGHT - 1;
	// 광선이 부딪힌 벽의 색상값에 따라 표현할 색상을 선택
	int color;
	if (game->map[mapY][mapX] == '1')
	{
		color = RGB_Green;
	}
	// else
	// {
	// 	color = RGB_Blue;
	// }

	//give x and y sides different brightness
	if (side == 1)
		color = color/2;
	draw_longitude_line(game, line, drawStart,drawEnd,color);
	line++;
	}
}
