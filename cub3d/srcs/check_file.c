/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:24:52 by tson              #+#    #+#             */
/*   Updated: 2023/01/22 18:11:54 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	check_arg(int argc, char *argv[], t_game *game)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || is_valid_file_name(argv[1]) == FALSE || fd == OPEN_FAIL)
		error_handle(INVALID_PROG_ARG_MES);
	set_max_map(game, fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	set_textures_and_colors(game, fd);
	set_map(game, fd);
	init_map(game);
}

t_bool	is_valid_file_name(char *file_name)
{
	int	idx;

	idx = ft_strchr(file_name, '.');
	if (idx == -1 || ft_strncmp(file_name + idx, FILE_EXTENSION,
			ft_strlen(file_name + idx)) != SAME_STR)
		return (FALSE);
	return (TRUE);
}
