/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:41:19 by joushin           #+#    #+#             */
/*   Updated: 2022/08/24 18:28:59 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_len(long long num)
{
	int	len;

	len = 1;
	if (num < 0)
	{
		len++;
		num *= -1;
	}
	while (num > 9)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_lltoa(long long n)
{
	int			len;
	char		*retstr;
	long long	num;

	num = n;
	len = check_len(num);
	retstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!retstr)
		return (0);
	retstr[len] = '\0';
	len--;
	if (num < 0)
	{
		retstr[0] = '-';
		num = num * -1;
	}
	if (num == 0)
		retstr[0] = '0';
	while (num)
	{
		retstr[len] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	return (retstr);
}

int	ft_putnbr_base(unsigned int nbr, char *base)
{
	int	ret_len;
	int	tmp_len;

	ret_len = 0;
	if (nbr < 16)
		return (write(1, &base[nbr], 1));
	tmp_len = ft_putnbr_base(nbr / 16, base);
	if (tmp_len == -1)
		return (-1);
	ret_len += tmp_len;
	tmp_len = write(1, &base[nbr % 16], 1);
	if (tmp_len == -1)
		return (-1);
	ret_len++;
	return (ret_len);
}

int	ft_print_addr(void *addr)
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
	if (write(1, "0x", 2) < 0)
		return (-1);
	if (write(1, memory + i, 16 - i) < 0)
		return (-1);
	if (i == 16)
		return (2 + write(1, "0", 1));
	return (2 + 16 - i);
}
