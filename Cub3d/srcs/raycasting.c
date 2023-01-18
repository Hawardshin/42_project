/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:43:54 by joushin           #+#    #+#             */
/*   Updated: 2023/01/18 22:20:02 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ray_casting(t_game *game)
{
	int	line;

	line =0;
	//line이 곧 스크린의 한줄씩을 의미한다.
	while (line < game->width)
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
		double cameraX = (2 * line) / game->width -1;
		double rayDirX = game->dir_x + game->plane_x * cameraX;
		double rayDirY = game->dir_y + game->plane_y * cameraX;
		/*
		광선의 방향은 ( 방향벡터 ) + ( 카메라평면 x 배수 )
		*/
		//현재 지도에서 내가 위치한 위치벡터
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
		double perpWallDist;
		// x로 갈지 Y로 갈지 정한다.
		// -1이나 1로 정한다.
		int stepX;
		int stepY;

		//
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//--------------------DDA용 변수------------------//

		line++;
	}
}
