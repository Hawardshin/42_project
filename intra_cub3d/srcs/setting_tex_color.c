/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_tex_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:52:42 by tson              #+#    #+#             */
/*   Updated: 2023/01/22 15:49:52 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	set_textures_and_colors(t_game *game, int fd)
{
	char	*str;
	char	**splits;

	str = get_next_line_no_nl(fd);
	while (str != NULL)
	{
		if (ft_strncmp(str, "", ft_strlen(str)) == SAME_STR)
		{
			free(str);
			str = get_next_line_no_nl(fd);
			continue ;
		}
		splits = ft_split(str, ' ');
		if (splits == NULL)
			error_handle(MALLOC_FAIL_MES);
		if (splits[0] == NULL || splits[1] == NULL || splits[2] != NULL)
			error_handle(FILE_CONFIG_ERR_MES);
		setting_tex_and_color(game, splits[0], splits[1]);
		free_strs(str, splits);
		if (is_setting_tex_and_color_end(game))
			break ;
		str = get_next_line_no_nl(fd);
	}
	if (is_setting_tex_and_color_end(game) == FALSE)
		error_handle(FILE_CONFIG_ERR_MES);
}

void	setting_tex_and_color(t_game *game, char *id, char *value)
{
	if (is_valid_id(game, id) == FALSE)
		error_handle(FILE_CONFIG_ERR_MES);
	if (is_texture_id(game, id) == TRUE)
		set_texture(game, id_to_idx_tex(id), value);
	else
		set_color(game, id_to_idx_color(id), value);
}

void	set_texture(t_game *game, int idx, char *xpm_name)
{
	int	fd;

	fd = open(xpm_name, O_RDONLY);
	if (fd == OPEN_FAIL)
		error_handle(XPM_FILE_NAME_ERR_MES);
	if (game->textures[idx].img != NULL)
		error_handle(SAME_ID_ERR_MES);
	game->textures[idx].img = mlx_xpm_file_to_image(game->mlx, xpm_name,
			&game->textures[idx].width, &game->textures[idx].height);
	game->textures[idx].data = (int *)mlx_get_data_addr(game->textures[idx].img,
			&game->textures[idx].bpp, &game->textures[idx].size_line,
			&game->textures[idx].endian);
}

void	set_color(t_game *game, int idx, char *str)
{
	int		i;
	int		num;
	char	**splits;

	splits = ft_split(str, ',');
	if (splits == NULL)
		error_handle(MALLOC_FAIL_MES);
	if (game->colors[idx] != COLOR_NOT_SET)
		error_handle(RGB_COLOR_ERR_MES);
	if (splits[0] == NULL || splits[1] == NULL
		|| splits[2] == NULL || splits[3] != NULL)
		error_handle(RGB_COLOR_ERR_MES);
	i = 0;
	game->colors[idx] = 0;
	while (i < 3)
	{
		game->colors[idx] <<= 8;
		num = ft_atoi(splits[i]);
		if (num < COLOR_MIN || num > COLOR_MAX)
			error_handle(RGB_COLOR_ERR_MES);
		game->colors[idx] += num;
		i++;
	}
	free_strs(NULL, splits);
}
