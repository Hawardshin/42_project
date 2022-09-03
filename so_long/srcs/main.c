/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:53:04 by joushin           #+#    #+#             */
/*   Updated: 2022/09/03 15:51:31 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"

void	parseimage(void	*win, void	*mlx)
{
	void	*img;
	void	*img2;
	// void	*img3;
	void	*img4;
	void	*img5;
	// void	*img6;
	// void	*img7;
	int img_width;
	int img_height;

	img = mlx_xpm_file_to_image(mlx, "./asset/land.xpm", &img_width, &img_height);
	img2 = mlx_xpm_file_to_image(mlx, "./asset/wall.xpm", &img_width, &img_height);
	img4 = mlx_xpm_file_to_image(mlx, "./asset/chest.xpm", &img_width, &img_height);
	img5 = mlx_xpm_file_to_image(mlx, "./asset/chest_open.xpm", &img_width, &img_height);
	// img6 = mlx_xpm_file_to_image(mlx, "./images/rune.xpm", &img_width, &img_height);
	// img7 = mlx_xpm_file_to_image(mlx, "./images/rune_light.xpm", &img_width, &img_height);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_put_image_to_window(mlx, win, img2, 64, 0);
	mlx_put_image_to_window(mlx, win, img4, 192, 64);
	mlx_put_image_to_window(mlx, win, img5, 0, 64);
	// mlx_put_image_to_window(mlx, win, img6, 64, 64);
	// mlx_put_image_to_window(mlx, win, img7, 128, 64);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_param	param;

	param_init(&param);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "so_long_project");
	parseimage(win, mlx);
	mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_press, &param);
	mlx_loop(mlx);
}
