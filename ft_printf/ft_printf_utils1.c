/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:39:26 by joushin           #+#    #+#             */
/*   Updated: 2022/07/21 16:45:34 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include "./includes/libft.h"

int	print_dec_int(va_list ap)
{
	char	*to_print;
	int		read_len;

	to_print = ft_lltoa(va_arg(ap, int));
	if (!to_print)
		return (-1);
	read_len = ft_putstr_fd(to_print, 1);
	free(to_print);
	to_print = NULL;
	return (read_len);
}

int	print_char(va_list ap)
{
	return (ft_putchar_fd(va_arg(ap, int), 1));
}

int	print_addr(va_list ap)
{
	void	*p;

	p = va_arg(ap, void *);
	return (ft_print_addr(p));
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

int	print_unsigned_int(va_list ap)
{
	char	*to_print;
	int		read_len;

	to_print = ft_lltoa(va_arg(ap, unsigned int));
	if (!to_print)
		return (-1);
	read_len = ft_putstr_fd(to_print, 1);
	free(to_print);
	to_print = NULL;
	return (read_len);
}

int	print_hex_lower(va_list ap)
{
	return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef"));
}

int	print_hex_upper(va_list ap)
{
	return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF"));
}

int	print_persent(va_list ap)//THINK
{
	(void)ap;
	return (write(1, "%%",1));
}
