/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:22:21 by joushin           #+#    #+#             */
/*   Updated: 2023/01/19 22:49:14 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


char	*check_file(char *line)
{
	int	fd;

	line += 2;
	while (*line == ' ' || *line == '\n')
		line++;
	fd = open(line, O_RDONLY);
	if (fd == -1)
		error_handle("can't open This file format\n");
	close(fd);
	return (line);
}

void	parse_one_line(t_game *game, char *line, char c)
{
	if (c == 'N')
		game->asset.no_path = check_file(line);
	else if (c == 'S')
		game->asset.so_path = check_file(line);
	else if (c == 'W')
		game->asset.we_path = check_file(line);
	else if (c == 'E')
		game->asset.ea_path = check_file(line);
	else
		error_handle("can't open This file format\n");
}

void	parse_files(t_game *game, char *line, char c)
{

}

void	parse_image_rgb(char *map_file, t_game *data)
{
	int		o_fd;
	char	*str;
	int		len;

	o_fd = open(map_file, O_RDONLY);
	if (o_fd == -1)
		error_handle("not exist cub\n");
	str = get_next_line(o_fd);
	if (!str)
		error_handle("cub format error\n");
	while (*str == )
	parse_one_line(data, str, *str);
	// int	img_width;
	// int	img_height;

	// data->land = mlx_xpm_file_to_image (mlx, \
	// "./asset/land.xpm", &img_width, &img_height);
	// data->wall = mlx_xpm_file_to_image(mlx, \
	// "./asset/wall.xpm", &img_width, &img_height);
	// data->chest = mlx_xpm_file_to_image(mlx, \
	// "./asset/chest.xpm", &img_width, &img_height);
	// data->chest_open = mlx_xpm_file_to_image(mlx, \
	// "./asset/chest_open.xpm", &img_width, &img_height);
	// data->play = mlx_xpm_file_to_image(mlx, \
	// "./asset/player.xpm", &img_width, &img_height);
	// data->out = mlx_xpm_file_to_image(mlx, \
	// "./asset/out_path.xpm", &img_width, &img_height);
}
