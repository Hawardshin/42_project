/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum_fuc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:25:07 by joushin           #+#    #+#             */
/*   Updated: 2022/07/22 08:19:13 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

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

int	print_addr(va_list ap)
{
	void	*p;

	p = va_arg(ap, void *);
	return (ft_print_addr(p));
}

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
