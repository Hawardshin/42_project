/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:49:27 by joushin           #+#    #+#             */
/*   Updated: 2022/08/26 15:49:58 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	eprint_char(va_list ap)
{
	return (ft_putchar_fd(va_arg(ap, int), 2));
}

int	eprint_str(va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
	{
		write(2, "(null)", 6);
		return (6);
	}
	return (ft_putstr_fd(str, 2));
}

int	eprint_persent(va_list ap)
{
	(void)ap;
	return (write(2, "%%", 1));
}
