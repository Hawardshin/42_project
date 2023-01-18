/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:05:43 by joushin           #+#    #+#             */
/*   Updated: 2023/01/16 19:54:49 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	map_parse(char *map_file, t_game *data)
{//한줄씩 맵 받기
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

void	file_chk(int argc, char **argv)
{
	if (argc != 2)
		error_handle("no map\n");
	if (!argv[1] || ft_strlen(argv[1]) < 4)
		error_handle("map name error\n");
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		error_handle("map name error\n");
}

int main(int argc, char ** argv)
{
	t_game	data;
	file_chk(argc, argv);
	map_parse(argv[1],&data);
	//맵 체크 해주고 map_check();
	data.mlx = mlx_init();
	if (!data.mlx)
		error_handle("can't open new window\n");
	//이미지 파싱하기
	data.win = mlx_new_window(data.mlx, \
	data.width * 64, data.high * 64, "./so_long");
	mlx_hook(data.win, X_EVENT_KEY_RELEASE, 0, &key_press, &data);
	mlx_hook(data.win, X_EVENT_KEY_EXIT, 0, &exit_game, &data);
	mlx_loop(data.mlx);
}
