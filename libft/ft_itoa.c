/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 07:10:23 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 22:24:25 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	check_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*retstr;

	len = check_len(n);
	retstr = (char *)malloc(sizeof(char) * len + 1);
	if (!retstr)
		return (0);
	retstr[len] = '\0';
	len--;
	if (n < 0)
	{
		retstr[0] = '-';
		retstr[len] = -1 * (n % 10) + '0';
		n = (n / 10) * -1;
		len--;
	}
	while (n >= 10)
	{
		retstr[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	if (retstr[len] != '-')
		retstr[len] = n + '0';
	return (retstr);
}
#include<stdio.h>
int main()
{
	printf("%s\n",ft_itoa(0));
	printf("%s\n",ft_itoa(0));
	printf("%s\n",ft_itoa(-1));
	printf("%s\n",ft_itoa(-1000));
	printf("%s\n",ft_itoa(-23233));
	printf("%s\n",ft_itoa(1));
	printf("%s\n",ft_itoa(42));
}
