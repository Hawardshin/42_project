/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:39:14 by joushin           #+#    #+#             */
/*   Updated: 2022/08/24 17:43:20 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_fuc_pointer(int (*fuc[256])(va_list ap), char *infuc)
{
	ft_memset(fuc, 0, 256);
	ft_memset(infuc, 0, 256);
	fuc['d'] = print_dec_int;
	fuc['i'] = print_dec_int;
	fuc['c'] = print_char;
	fuc['p'] = print_addr;
	fuc['s'] = print_str;
	fuc['u'] = print_unsigned_int;
	fuc['x'] = print_hex_lower;
	fuc['X'] = print_hex_upper;
	fuc['%'] = print_persent;
	infuc['d'] = 1;
	infuc['i'] = 1;
	infuc['c'] = 1;
	infuc['p'] = 1;
	infuc['s'] = 1;
	infuc['u'] = 1;
	infuc['x'] = 1;
	infuc['X'] = 1;
	infuc['%'] = 1;
}

int	ft_printf(const char *args, ...)
{
	va_list	ap;
	int		ret_cnt;
	int		(*fuc[256])(va_list ap);
	char	infuc[256];
	int		cnt_tmp;

	init_fuc_pointer(fuc, infuc);
	ret_cnt = 0;
	cnt_tmp = 0;
	if (!args)
		return (-1);
	va_start(ap, args);
	while (*args && cnt_tmp != -1)
	{
		if ((unsigned char)(*args) == '%' && infuc[(unsigned char)(*(++args))])
				cnt_tmp = fuc[(unsigned char)(*args++)](ap);
		else
			cnt_tmp = write(1, args++, 1);
		ret_cnt += cnt_tmp;
	}
	va_end(ap);
	if (cnt_tmp < 0)
		return (-1);
	return (ret_cnt);
}
