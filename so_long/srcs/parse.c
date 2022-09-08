/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:56:06 by joushin           #+#    #+#             */
/*   Updated: 2022/09/08 15:43:05 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"
#include "./libft/libft.h"

void	parse_image(void *mlx, t_game *data)
{
	int	img_width;
	int	img_height;

	data->land = mlx_xpm_file_to_image (mlx, \
	"./asset/land.xpm", &img_width, &img_height);
	data->wall = mlx_xpm_file_to_image(mlx, \
	"./asset/wall.xpm", &img_width, &img_height);
	data->chest = mlx_xpm_file_to_image(mlx, \
	"./asset/chest.xpm", &img_width, &img_height);
	data->chest_open = mlx_xpm_file_to_image(mlx, \
	"./asset/chest_open.xpm", &img_width, &img_height);
	data->player = mlx_xpm_file_to_image(mlx, \
	"./asset/player.xpm", &img_width, &img_height);
	data->out_path = mlx_xpm_file_to_image(mlx, \
	"./asset/out_path.xpm", &img_width, &img_height);
}

void	map_parse(char *map_file, t_game *data)
{
	int		o_fd;
	char	*str;

	o_fd = open(map_file, O_RDONLY);
	if (o_fd == -1)
		error_handle("not exist map\n");
	str = get_next_line(o_fd);
	if (!str)
		error_handle("map format error\n");
	data->map = ft_strdup_no_nl(str);
	data->width = (int)ft_strlen(str) - 1;
	data->high = 0;
	while (str)
	{
		free(str);
		data->high++;
		str = get_next_line(o_fd);
		if (str)
		{
			data->map = ft_strjoin_no_nl(data->map, str);
			if (data->width != ((int)ft_strlen(str) - 1))
				error_handle("map format error\n");
		}
	}
	// printf("%d %d\n", data->high, data->width);
	close(o_fd);
}

void	chk_map(t_game data)
{
	int	e_cnt;
	int	p_cnt;
	int	c_cnt;
	int	i;

	i = -1;
	e_cnt = 0;
	c_cnt = 0;
	p_cnt = 0;
	while (data.map[++i])
	{
		if ((!(i / data.width) || !(data.width % (i + 1)) || \
		!(data.width % i)) && (data.map[i] != '1'))
			error_handle("1map format error\n");
		if (data.map[i] == 'E')
			e_cnt++;
		else if (data.map[i] == 'P')
			p_cnt++;
		else if (data.map[i] == 'C')
			c_cnt++;
		else if (data.map[i] != '0' && data.map[i] != '1')
			error_handle("2map format error\n");
	}
	if (c_cnt != 1 || p_cnt != 1 || e_cnt == 0)
		error_handle("3map format error\n");
}
