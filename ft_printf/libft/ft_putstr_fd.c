/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 06:47:32 by joushin           #+#    #+#             */
/*   Updated: 2022/07/20 16:58:16 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	w_ret;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (ft_putchar_fd(s[i++], fd) == -1)
			return (-1);
	}
	return (i);
}
