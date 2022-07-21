/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:39:26 by joushin           #+#    #+#             */
/*   Updated: 2022/07/21 17:33:19 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include "./includes/libft.h"

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
