/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:04:18 by joushin           #+#    #+#             */
/*   Updated: 2023/01/16 13:26:07 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Character '북' on the screen means 'North' in Korean.
#include <stdio.h>
#include "../mlx/mlx.h"
#include <stdio.h>
int main()
{
		void *mlx;
		void *win;
		void *img;

		int	img_width;
		int	img_height ;

		mlx = mlx_init();
		win = mlx_new_window(mlx, 500, 500, "my_mlx");
		img = mlx_xpm_file_to_image(mlx, "./example/wall.xpm", &img_width, &img_height);
		printf("wid : %d high : %d",img_width,img_height);
		mlx_put_image_to_window(mlx, win, img, 300, 300); //뒤에 2개는 좌표
		mlx_loop(mlx);
		return (0);
}
