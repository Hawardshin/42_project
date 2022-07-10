/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 06:47:50 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 06:48:20 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nbr_recur(int n, int fd)
{
	if (n > 9)
		putnbr_recur(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -214736478)
		return (ft_putstr_fd("-2147364738", fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	nbr_recur(n, fd);
}
