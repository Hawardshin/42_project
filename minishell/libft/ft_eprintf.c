/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:48:51 by joushin           #+#    #+#             */
/*   Updated: 2022/08/24 18:14:23 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_efuc_pointer(int (*fuc[256])(va_list ap), char *infuc)
{
	ft_memset(fuc, 0, 256);
	ft_memset(infuc, 0, 256);
	fuc['d'] = eprint_dec_int;
	fuc['i'] = eprint_dec_int;
	fuc['c'] = eprint_char;
	fuc['p'] = eprint_addr;
	fuc['s'] = eprint_str;
	fuc['u'] = eprint_unsigned_int;
	fuc['x'] = eprint_hex_lower;
	fuc['X'] = eprint_hex_upper;
	fuc['%'] = eprint_persent;
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

int	ft_eprintf(const char *args, ...)
{
	va_list	ap;
	int		ret_cnt;
	int		(*fuc[256])(va_list ap);
	char	infuc[256];
	int		cnt_tmp;

	init_efuc_pointer(fuc, infuc);
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
			cnt_tmp = write(2, args++, 1);
		ret_cnt += cnt_tmp;
	}
	va_end(ap);
	if (cnt_tmp < 0)
		return (-1);
	return (ret_cnt);
}
