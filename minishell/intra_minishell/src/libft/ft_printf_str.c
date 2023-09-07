/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:48:51 by joushin           #+#    #+#             */
/*   Updated: 2022/08/26 15:50:07 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
