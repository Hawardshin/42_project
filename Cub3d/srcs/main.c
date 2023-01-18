/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:05:43 by joushin           #+#    #+#             */
/*   Updated: 2023/01/18 14:29:03 by joushin          ###   ########.fr       */
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
	data->map = malloc(sizeof (char *) * 500);//새로줄 일단 500 정도로 놓고 시작하기
	data->map[0] = ft_strdup_no_nl(str);
	data->high = 0;
	while (str)
	{
		free(str);
		data->high++;
		str = get_next_line(o_fd);
		if (str)
			data->map[data->high] = ft_strdup_no_nl(str);
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

void	print_map(t_game *data)
{
	for (int i=0; i < data->high;i++)
	{
		for(int j =0;j < (int)ft_strlen(data->map[i]);j++)
		{
			printf("%c",data->map[i][j]);
		}
		printf("\n");
	}
}

void	init_map(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	g->dir_x = 0;
	g->dir_y = 0;
	g->angle = 0;
	g->x = -1;
	g->y = -1;
	while (i < g->high)
	{
		j=0;
		while (j < (int)ft_strlen(g->map[i]))
		{
			if (g->map[i][j] == 'N' || g->map[i][j] == 'S'|| g->map[i][j] == 'E' || g->map[i][j] == 'W')
			{
				if (g->x != -1 || g->x != -1)
					error_handle("ONLY ONE PLAYER CAN PLAY\n");
				g->x = j;
				g->y = i;
				if (g->map[i][j] == 'N')
				{
					g->dir_x = 0;
					g->dir_y = 1;
					g->angle = 90;
				}
				else if (g->map[i][j] == 'S')
				{
					g->dir_x = 0;
					g->dir_y = -1;
					g->angle = 270;
				}
				else if (g->map[i][j] == 'E')
				{
					g->dir_x = 1;
					g->dir_y = 0;
					g->angle = 0;
				}
				else ////W
				{
					g->dir_x = -1;
					g->dir_y = 0;
					g->angle = 180;
				}
			}
			j++;
		}
		i++;
	}
}

int main(int argc, char ** argv)
{
	t_game	data;
	file_chk(argc, argv);
	map_parse(argv[1],&data);//일단은 다른 것 말고 지도만 있다고 생각하고 지도만 받을 것
	//맵 체크 해주고 map_check();
	print_map(&data);
	init_map(&data);//여기서 예외 처리랑 다른 것들을 처리한다.
	data.mlx = mlx_init();
	if (!data.mlx)
		error_handle("can't open new window\n");
	//이미지 파싱하기
	data.width = 10;
	data.win = mlx_new_window(data.mlx, \
	data.width * 64, data.high * 64, "./cub3d");
	// mlx_hook(data.win, X_EVENT_KEY_RELEASE, 0, &key_press, &data);
	// mlx_hook(data.win, X_EVENT_KEY_EXIT, 0, &exit_game, &data);
	mlx_loop(data.mlx);
}
