/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:53:04 by joushin           #+#    #+#             */
/*   Updated: 2023/01/18 11:53:26 by joushin          ###   ########.fr       */
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

void	file_chk(int argc, char **argv)
{
	if (argc <= 1)
		error_handle("no map\n");
	if (!argv[1] || ft_strlen(argv[1]) < 4)
		error_handle("map name error\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
		error_handle("map name error\n");
}

int	main(int argc, char **argv)
{
	t_game	data;

	file_chk(argc, argv);
	map_parse(argv[1], &data);
	chk_map(&data);
	data.mlx = mlx_init();
	if (!data.mlx)
		error_handle("can't open new window\n");
	parse_image(data.mlx, &data);
	if (128 < data.width || 128 < data.high)
		error_handle("too big map\n");
	data.win = mlx_new_window(data.mlx, \
	data.width * 64, data.high * 64, "./so_long");
	param_init(&data);
	img_set(data);
	mlx_hook(data.win, X_EVENT_KEY_RELEASE, 0, &key_press, &data);
	mlx_hook(data.win, X_EVENT_KEY_EXIT, 0, &exit_game, &data);
	mlx_loop(data.mlx);
}
