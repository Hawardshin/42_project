/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:28:26 by joushin           #+#    #+#             */
/*   Updated: 2022/07/08 16:20:40 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if (result > 9223372036854775807 && sign == -1)
		return (0);
	else if (result > 9223372036854775807)
		return (-1);
	else
		return ((int)sign * result);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	printf("%d\n",atoi("-2147364748"));
// 	printf("%d\n",atoi("--2147364748"));
// 	printf("%d\n",atoi("-+214736474"));
// 	printf("%d\n",atoi("--214736474"));
// 	printf("%d\n",atoi("4294729475"));
// 	printf("%d\n",atoi("9223372036854775805"));
// 	printf("%d\n",atoi("9223372036854775806"));
// 	printf("%d\n",atoi("9223372036854775807"));
// 	printf("%d\n",atoi("9223372036854775808"));
// 	printf("%d\n",atoi("9223372036854775809"));
// 	printf("%d\n",atoi("18446744073709551615512345412332532323"));
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("%d\n",ft_atoi("-2147364748"));
// 	printf("%d\n",ft_atoi("--2147364748"));
// 	printf("%d\n",ft_atoi("-+214736474"));
// 	printf("%d\n",ft_atoi("--214736474"));
// 	printf("%d\n",ft_atoi("4294729475"));
// 	printf("%d\n",ft_atoi("9223372036854775805"));
// 	printf("%d\n",ft_atoi("9223372036854775806"));
// 	printf("%d\n",ft_atoi("9223372036854775807"));
// 	printf("%d\n",ft_atoi("9223372036854775808"));
// 	printf("%d\n",ft_atoi("9223372036854775809"));
// 	printf("%d\n",ft_atoi("9223372036854775810"));
// }
