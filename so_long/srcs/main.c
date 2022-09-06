/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:53:04 by joushin           #+#    #+#             */
/*   Updated: 2022/09/06 20:50:47 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"
#include "./libft/libft.h"

void	img_set(t_game g)
{
	int	hi;
	int	wi;

	hi = -1;
	while (++hi < g.high)
	{
		wi = -1;
		while (++wi < g.width)
		{
			if (g.map[hi * g.width + wi] == '1')
				mlx_put_image_to_window(g.mlx, g.win, \
				g.wall, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == 'C')
				mlx_put_image_to_window(g.mlx, g.win, \
				g.chest, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == 'P')
				mlx_put_image_to_window(g.mlx, g.win, \
				g.player, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == 'E')
				mlx_put_image_to_window(g.mlx, g.win, \
				g.out_path, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == '0')
				mlx_put_image_to_window(g.mlx, g.win, g.land, wi * 64, hi * 64);
		}
	}
}

int	main(int argc, char **argv)///최대크기 , 맵파일 이름, x눌렀을때 끄는거
{
	void	*mlx;
	void	*win;
	t_param	param;
	t_game	data;

	if (argc > 1)
	{
		map_parse(argv[1], &data);
		chk_map(data);
		mlx = mlx_init();
		parse_image(mlx, &data);
		printf("%d %d", data.high, data.width);
		win = mlx_new_window(mlx, data.width * 64, data.high * 64, "./so_long");
		data.win = win;
		data.mlx = mlx;
		param_init(&param, data);
		// for (int i=0; i < data.high; i++)
		// {
		// 	for (int j = 0; j < data.width; j++)
		// 	{
		// 		printf("%c ", data.map[i * data.width + j]);
		// 	}
		// 	printf("\n");
		// }
		img_set(data);
		mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_press, &param);
		mlx_loop(mlx);
	}
}
