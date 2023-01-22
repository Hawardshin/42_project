/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_tex_color_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:54:49 by tson              #+#    #+#             */
/*   Updated: 2023/01/22 13:54:50 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

t_bool	is_setting_tex_and_color_end(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img == NULL)
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (game->colors[i] == COLOR_NOT_SET)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	id_to_idx_tex(char *id)
{
	if (ft_strncmp(id, NO_ID, ft_strlen(id)) == SAME_STR)
		return (NORTH);
	if (ft_strncmp(id, SO_ID, ft_strlen(id)) == SAME_STR)
		return (SOUTH);
	if (ft_strncmp(id, WE_ID, ft_strlen(id)) == SAME_STR)
		return (WEST);
	return (EAST);
}

int	id_to_idx_color(char *id)
{
	if (ft_strncmp(id, F_ID, ft_strlen(id)) == SAME_STR)
		return (FLOOR);
	return (CEILING);
}

t_bool	is_valid_id(t_game *game, char *id)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(id, game->identifiers[i], ft_strlen(id)) == SAME_STR)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_texture_id(t_game *game, char *id)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(id, game->identifiers[i], ft_strlen(id)) == SAME_STR)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
