/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:22:21 by joushin           #+#    #+#             */
/*   Updated: 2023/01/20 14:17:16 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// char	*check_file(char *line)
// {
// 	int	fd;

// 	line += 2;
// 	while (*line == ' ' || *line == '\n')
// 		line++;
// 	fd = open(line, O_RDONLY);
// 	if (fd == -1)
// 		error_handle("can't open This file format\n");
// 	close(fd);
// 	return (line);
// }

// void	parse_one_line(t_game *game, char *line, char c)
// {
// 	if (c == 'N')
// 		game->asset.no_path = check_file(line);
// 	else if (c == 'S')
// 		game->asset.so_path = check_file(line);
// 	else if (c == 'W')
// 		game->asset.we_path = check_file(line);
// 	else if (c == 'E')
// 		game->asset.ea_path = check_file(line);
// 	else
// 		error_handle("can't open This file format\n");
// }

// void	parse_files(t_game *game, char *line, char c)
// {

// }

void	parse_image_rgb(void *mlx, t_game *data)
{
	// int		o_fd;
	// char	*str;
	// int		len;

	// o_fd = open(map_file, O_RDONLY);
	// if (o_fd == -1)
	// 	error_handle("not exist cub\n");
	// str = get_next_line(o_fd);
	// if (!str)
	// 	error_handle("cub format error\n");
	// while (*str == )
	// parse_one_line(data, str, *str);
	int	img_width;
	int	img_height;

	data->asset.no_img.img = mlx_xpm_file_to_image (mlx, \
	"./file/chatgpt.xpm", &img_width, &img_height);

	data->asset.no_img.data=(int *)mlx_get_data_addr(data->asset.no_img.img, \
	&data->asset.no_img.bpp, &data->asset.no_img.size_l, &data->asset.no_img.endian);
	//
	data->asset.so_img.img = mlx_xpm_file_to_image(mlx, \
	"./file/eagle.xpm", &img_width, &img_height);

	// data->asset.so_img.data=(int *)mlx_get_data_addr(data->asset.so_img.img, \
	// &data->asset.so_img.bpp, &data->asset.so_img.size_l, &data->asset.so_img.endian);
	// //
	// data->asset.ea_img.img = mlx_xpm_file_to_image(mlx, \
	// "./file/purplestone.xpm", &img_width, &img_height);

	// data->asset.ea_img.data=(int *)mlx_get_data_addr(data->asset.ea_img.img, \
	// &data->asset.ea_img.bpp, &data->asset.ea_img.size_l, &data->asset.ea_img.endian);
	// //
	// data->asset.we_img.img = mlx_xpm_file_to_image(mlx, \
	// "./file/redbrick.xpm", &img_width, &img_height);

	// data->asset.we_img.data=(int *)mlx_get_data_addr(data->asset.we_img.img, \
	// &data->asset.we_img.bpp, &data->asset.we_img.size_l, &data->asset.we_img.endian);

}
