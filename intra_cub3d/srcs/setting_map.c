/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:03:50 by tson              #+#    #+#             */
/*   Updated: 2023/01/23 14:20:09 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	change_space(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->map_high)
	{
		j = 0;
		while (j < g->map_wid[i])
		{
			if (check_type(g->map[i][j]) == SPACE)
				g->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	init_map(t_game *g)
{
	t_move_arr	ar;
	int			i;
	int			j;

	i = 0;
	init_mapping(&ar, g);
	check_around_wall(g, ar);
	while (i < g->map_high)
	{
		j = 0;
		while (j < g->map_wid[i])
		{
			if (check_type(g->map[i][j]) == ERROR)
				error_handle("INVALID CHAR IN MAP\n");
			if (check_type(g->map[i][j]) == PLAYER)
				init_player(g, i, j);
			if (check_type(g->map[i][j]) == SPACE)
				g->map[i][j] = '1';
			j++;
		}
		i++;
	}
	if (g->p_info.pos.x == -1 && g->p_info.pos.y == -1)
		error_handle("NO PLAYER\n");
}

t_bool	check_all_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n'))
	{
		i++;
	}
	if (str[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

void	set_map(t_game *game, int fd)
{
	char	*str;

	str = pass_nl_first_init(game, fd);
	while (str)
	{
		free(str);
		game->map_high++;
		str = get_next_line(fd);
		if (str)
		{
			if (check_all_white_space(str))
				error_handle("INVAILD MAP FORMAT\n");
			game->map[game->map_high] = ft_strdup_no_nl(str);
			game->map_wid[game->map_high] = \
			ft_strlen(game->map[game->map_high]);
		}
	}
	game->map[game->map_high] = NULL;
	close(fd);
}
