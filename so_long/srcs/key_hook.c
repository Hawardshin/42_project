/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:26:08 by joushin           #+#    #+#             */
/*   Updated: 2022/09/06 20:57:05 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../mlx/mlx.h"
#include "./libft/libft.h"

void	param_init(t_param *param, t_game g)
{
	int	hi;
	int	wi;

	hi = -1;
	while (++hi < g.high)
	{
		wi = -1;
		while (++wi < g.width)
		{
			if (g.map[hi * g.width + wi] == 'P')
			{
				param->x = wi;
				param->y = hi;
			}
		}
	}
}

int	key_press(int keycode, t_param *param, t_game *data)
{
	if (keycode == KEY_W)
		move_w(param, data);
	else if (keycode == KEY_S)
		move_s(param, data);
	else if (keycode == KEY_A)
		move_a(param, data);
	else if (keycode == KEY_D)
		move_d(param, data);
	else if (keycode == KEY_ESC)
		exit_game(param, data);
	printf("x : %d y : %d\n", param->x, param->y);
	return (0);
}
