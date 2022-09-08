/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:51:45 by joushin           #+#    #+#             */
/*   Updated: 2022/09/08 15:38:54 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# include <fcntl.h> //open
# include <stdio.h> //printf perror
# include <stdlib.h> //exit, malloc free strerror printf
# include <unistd.h>

/*
open, close, read, write,
printf, malloc, free, perror,
strerror, exit
*/

typedef struct s_game
{
	int		x;
	int		y;
	int		str_line;
	int		high;
	int		width;
	char	*map;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*land;
	void	*player;
	void	*chest;
	void	*chest_open;
	void	*out_path;
}t_game;

void	img_set(t_game g);
void	param_init(t_game *g);
int		key_press(int keycode, t_game *data);

void	parse_image(void *mlx, t_game *data);
void	map_parse(char *map_file, t_game *data);
void	chk_map(t_game data);

void	error_handle(char *s);
void	error_handle(char *s);
char	*ft_strjoin_no_nl(char *dest, char *src);
char	*ft_strdup_no_nl(char *str);

void	move_w(t_game *data);
void	move_s(t_game *data);
void	move_a(t_game *data);
void	move_d(t_game *data);
void	exit_game(t_game *data);

#endif
