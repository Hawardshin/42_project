/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:53:04 by joushin           #+#    #+#             */
/*   Updated: 2022/09/05 20:49:14 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"
#include "./libft/libft.h"

void	parse_image(void *mlx, t_game *data)
{
	int	img_width;
	int	img_height;

	data->land = mlx_xpm_file_to_image (mlx, "./asset/land.xpm", &img_width, &img_height);
	data->wall = mlx_xpm_file_to_image(mlx, "./asset/wall.xpm", &img_width, &img_height);
	data->chest = mlx_xpm_file_to_image(mlx, "./asset/chest.xpm", &img_width, &img_height);
	data->chest_open = mlx_xpm_file_to_image(mlx, "./asset/chest_open.xpm", &img_width, &img_height);
	data->player = mlx_xpm_file_to_image(mlx, "./asset/player.xpm", &img_width, &img_height);
	data->out_path = mlx_xpm_file_to_image(mlx, "./asset/out_path.xpm", &img_width, &img_height);
}

void	error_handle(char *s)
{
	ft_eprintf("error\n");
	ft_eprintf("%s", s);
	exit(1);
}

char	*ft_strjoin_no_nl(char *dest, char *src)
{
	int		d_len;
	int		s_len;
	char	*ret;
	int		i;
	int		j;

	d_len = ft_strlen(dest);
	s_len = ft_strlen(src);
	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (d_len + s_len));
	if (!ret)
		error_handle("Memory allocate fail\n");
	while (dest[i])
	{
		ret[i] = dest[i];
		i++;
	}
	free(dest);
	while (src[j] && src[j] != '\n')
		ret[i++] = src[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strdup_no_nl(char *str)
{
	int		len;
	char	*ret;
	int		i;

	i = 0;
	len = ft_strlen(str);
	ret = (char *)malloc(sizeof(char) * len);
	if (!ret)
		error_handle("Memory allocate fail\n");
	while (str[i] && str[i] != '\n')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
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
	close(o_fd);
}

void	chk_map(t_game data)
{
	int	e_cnt;//E, P, C1개이상이어야함.
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

void	img_set(t_game data)
{
	int	high;
	int	width;

	high = 0;
	while (high < data.high)
	{
		width = 0;
		while (width < data.width)
		{
			// printf("%d ",data.map[high * data.width + width]);
			if (data.map[high * data.width + width] == '1')
				mlx_put_image_to_window(data.mlx, data.win, data.wall, width * 64, high * 64);
			else if (data.map[high * data.width + width] == 'C')
				mlx_put_image_to_window(data.mlx, data.win, data.chest, width * 64, high * 64);
			else if (data.map[high * data.width + width] == 'P')
				mlx_put_image_to_window(data.mlx, data.win, data.player, width * 64, high * 64);
			else if (data.map[high * data.width + width] == 'E')
				mlx_put_image_to_window(data.mlx, data.win, data.out_path, width * 64, high * 64);
			else if (data.map[high * data.width + width] == '0')
				mlx_put_image_to_window(data.mlx, data.win, data.land, width * 64, high * 64);
			else
				error_handle("error\n");
			width++;
		}
		// printf("\n");
		high++;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	t_param	param;
	t_game	data;

	if (argc > 1)
	{
		map_parse(argv[1], &data);
		chk_map(data);
		param_init(&param);
		mlx = mlx_init();
		parse_image(mlx, &data);
		printf("%d %d", data.high, data.width);
		win = mlx_new_window(mlx, data.width * 64, data.high * 64, "./so_long");
		data.win = win;
		data.mlx = mlx;
		for (int i=0; i < data.high; i++)
		{
			for (int j = 0; j < data.width; j++)
			{
				printf("%c ", data.map[i * data.width + j]);
			}
			printf("\n");
		}
		img_set(data);
		mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_press, &param);
		mlx_loop(mlx);
	}
}
