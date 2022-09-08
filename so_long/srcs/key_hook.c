/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:26:08 by joushin           #+#    #+#             */
/*   Updated: 2022/09/08 18:32:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../mlx/mlx.h"
#include "./libft/libft.h"

void	param_init(t_game *g)
{
	int	hi;
	int	wi;

	hi = -1;
	g->flag = 0;
	while (++hi < g->high)
	{
		wi = -1;
		while (++wi < g->width)
		{
			if (g->map[hi * g->width + wi] == 'P')
			{
				g->x = wi;
				g->y = hi;
			}
		}
	}
}

int	key_press(int keycode, t_game *param)
{
	if (keycode == KEY_W)
		move_w(param);
	else if (keycode == KEY_S)
		move_s(param);
	else if (keycode == KEY_A)
		move_a(param);
	else if (keycode == KEY_D)
		move_d(param);
	else if (keycode == KEY_ESC)
		exit_game(param);
	printf("x : %d y : %d\n", param->x, param->y);
	return (0);
}
