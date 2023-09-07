/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:03:44 by joushin           #+#    #+#             */
/*   Updated: 2023/01/23 13:45:48 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	make_max_map(t_game *game)
{
	int	i;

	i = 0;
	game->map = malloc(sizeof (char *) *(game->max_high));
	game->map_wid = malloc (sizeof (int) *(game->max_high));
	if (!game->map || !game->map_wid)
		error_handle("Memory allocate fail\n");
}

void	set_max_map(t_game *game, int fd)
{
	int		len;
	char	*str;

	game->max_high = 0;
	str = get_next_line(fd);
	if (!str)
		error_handle("map format error\n");
	len = ft_strlen(str);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		game->max_high++;
	}
	make_max_map(game);
}

char	*pass_nl_first_init(t_game *game, int fd)
{
	char	*str;
	int		len;

	str = get_next_line(fd);
	if (str == NULL)
		error_handle("map format error\n");
	while (str && check_all_white_space(str) == TRUE)
	{
		free(str);
		str = get_next_line(fd);
	}
	if (!str)
		error_handle("map format error\n");
	game->map[0] = ft_strdup_no_nl(str);
	len = ft_strlen(game->map[0]);
	game->map_wid[0] = len;
	game->map_high = 0;
	return (str);
}

void	init_player(t_game *g, int i, int j)
{
	if (g->p_info.pos.x != -1 || g->p_info.pos.y != -1)
		error_handle("ONLY ONE PLAYER CAN PLAY\n");
	g->p_info.pos.x = j + 0.5;
	g->p_info.pos.y = i + 0.5;
	if (g->map[i][j] == 'N')
	{
		g->p_info.dir.y = 1;
		g->p_info.plane.x = (VIEW_ANGLE * 1);
	}
	else if (g->map[i][j] == 'S')
	{
		g->p_info.dir.y = -1;
		g->p_info.plane.x = (VIEW_ANGLE * -1);
	}
	else if (g->map[i][j] == 'E')
	{
		g->p_info.dir.x = 1;
		g->p_info.plane.y = (VIEW_ANGLE * -1);
	}
	else
	{
		g->p_info.dir.x = -1;
		g->p_info.plane.y = (VIEW_ANGLE * 1);
	}
	g->map[i][j] = '0';
}
