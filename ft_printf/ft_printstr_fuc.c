/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr_fuc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:39:26 by joushin           #+#    #+#             */
/*   Updated: 2022/07/22 08:19:35 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

int	print_char(va_list ap)
{
	return (ft_putchar_fd(va_arg(ap, int), 1));
}

int	print_str(va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	return (ft_putstr_fd(str, 1));
}

int	print_persent(va_list ap)
{
	(void)ap;
	return (write(1, "%%", 1));
}
