/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:05:43 by joushin           #+#    #+#             */
/*   Updated: 2023/01/18 18:30:27 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	map_parse(char *map_file, t_game *data)
{//한줄씩 맵 받기
	int		o_fd;
	char	*str;
	int		len;

	o_fd = open(map_file, O_RDONLY);
	if (o_fd == -1)
		error_handle("not exist map\n");
	str = get_next_line(o_fd);
	if (!str)
		error_handle("map format error\n");
	data->map = malloc(sizeof (char *) * 500);//새로줄 일단 500 정도로 놓고 시작하기
	data->map[0] = ft_strdup_no_nl(str);
	len = ft_strlen(data->map[0]);
	data->width = len;
	data->high = 0;
	while (str)
	{
		free(str);
		data->high++;
		str = get_next_line(o_fd);
		if (str)
		{
			data->map[data->high] = ft_strdup_no_nl(str);
			len = ft_strlen(data->map[data->high]);
		}
		if (data->width < len)
			data->width = len;
	}
	// printf("%d\n",data->width);
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

t_map_type check_type(char a)
{
	if (a == 'N' || a == 'S'|| a == 'E' || a == 'W')
		return (PLAYER);
	else if (a == '1')
		return (WALL);
	else  if (a == '0' || a== ' ')
		return (EMPTY);
	else
		return(ERROR);
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
			if (check_type(g->map[i][j]) == ERROR)
				error_handle("INVALID CHAR IN MAP\n");
			if (check_type(g->map[i][j]) == PLAYER)
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

int		main_loop(t_game *game)
{
	draw_rectangles(game);
	draw_lines(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
void	img_init(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, game->width * TILE_SIZE, game->high * TILE_SIZE);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
}

double	y_direct(t_game *game,double angle);
double	x_direct(t_game *game,double angle);
void	draw_razer(t_game *game, double x1, double y1, double x2, double y2);

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
	data.win = mlx_new_window(data.mlx, \
	(data.width * TILE_SIZE) , (data.high * TILE_SIZE), "./cub3d");
	//이미지 파싱하기

	img_init(&data);
	// printf("x: %f, y: %f\n",x_direct(&data,45),y_direct(&data,45) );
	// mlx_hook(data.win, X_EVENT_KEY_RELEASE, 0, &key_press, &data);
	// mlx_hook(data.win, X_EVENT_KEY_EXIT, 0, &exit_game, &data);
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_loop(data.mlx);
}

