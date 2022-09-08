/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:53:04 by joushin           #+#    #+#             */
/*   Updated: 2022/09/08 18:34:08 by joushin          ###   ########.fr       */
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
				mlx_put_image_to_window(g.mlx, g.win, g.wall, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == 'C')
				mlx_put_image_to_window(g.mlx, g.win, \
				g.chest, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == 'P')
				mlx_put_image_to_window(g.mlx, g.win, g.play, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == 'E')
				mlx_put_image_to_window(g.mlx, g.win, g.out, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == '0')
				mlx_put_image_to_window(g.mlx, g.win, g.land, wi * 64, hi * 64);
			else if (g.map[hi * g.width + wi] == 'c')
				mlx_put_image_to_window(g.mlx, g.win, \
				g.chest_open, wi * 64, hi * 64);
		}
	}
}

int	main(int argc, char **argv) ///최대크기 , x눌렀을때 끄는거
{
	void	*mlx;
	void	*win;
	t_game	data;

	if (argc <= 1)
		error_handle("no map\n");
	if (!argv[1])
		error_handle("map name error\n");
	if (ft_strlen(argv[1]) < 4)
		error_handle("map name error\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
		error_handle("map name error\n");
	map_parse(argv[1], &data);
	chk_map(data);
	mlx = mlx_init();
	parse_image(mlx, &data);
	win = mlx_new_window(mlx, data.width * 64, data.high * 64, "./so_long");
	data.win = win;
	data.mlx = mlx;
	param_init(&data);
	img_set(data);
	mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_press, &data);
	mlx_hook(win, X_EVENT_KEY_EXIT, 0, &exit_game, &data);
	mlx_loop(mlx);
	printf("%d %d\n", data.high, data.width);//
}
