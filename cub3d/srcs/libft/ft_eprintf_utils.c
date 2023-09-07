/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:49:37 by joushin           #+#    #+#             */
/*   Updated: 2022/08/24 18:29:47 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_eputnbr_base(unsigned int nbr, char *base)
{
	int	ret_len;
	int	tmp_len;

	ret_len = 0;
	if (nbr < 16)
		return (write(2, &base[nbr], 1));
	tmp_len = ft_eputnbr_base(nbr / 16, base);
	if (tmp_len == -1)
		return (-1);
	ret_len += tmp_len;
	tmp_len = write(2, &base[nbr % 16], 1);
	if (tmp_len == -1)
		return (-1);
	ret_len++;
	return (ret_len);
}

int	ft_eprint_addr(void *addr)
{
	unsigned long long	ddr;
	int					i;
	char				memory[17];

	ddr = (unsigned long long)addr;
	i = 0;
	while (i < 16)
	{
		memory[15 - i] = "0123456789abcdef"[ddr % 16];
		ddr = ddr / 16;
		i++;
	}
	memory[16] = '\0';
	i = 0;
	while (memory[i] == '0')
		i++;
	if (write(2, "0x", 2) < 0)
		return (-1);
	if (write(2, memory + i, 16 - i) < 0)
		return (-1);
	if (i == 16)
		return (2 + write(2, "0", 1));
	return (2 + 16 - i);
}
