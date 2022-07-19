/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:25:44 by joushin           #+#    #+#             */
/*   Updated: 2022/07/19 17:46:24 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

int	ft_printf(const char *args, ...)
{
	va_list	ap;
	int		ret_count;

	ret_count = 0;
	if (!args)
		return (0);
	va_start(ap, args);
	while ( *args && ret_count != -1)
	{

	}
	return (0);
}

#include <stdio.h>
int test(int *ar, ...)
{
	va_list ap;
	va_start(ap, ar);
	//printf("%d",*ar);
	int result = 0;
	while (result != -1 && *ar)
	{
		result = va_arg(ap, int);
		//printf("%d",i);
		printf("%d\n",result);
		//ar++;
	}
	va_end(ap);
	return (0);
}


int main()
{
	// char* value = "asdf";
	// unsigned char *p= (unsigned char*)&value;
	// char *hex = "0123456789abcdef";

	// for (int i = 7; i >= 0; i--)
	// {
	// 	write(1, &hex[p[i] / 16], 1);
	// 	write(1, &hex[p[i] % 16], 1);
	// }
	// write(1, "\n", 1);
	// printf("%p\n", value);
	int input[6];
	for (int i= 0; i< 5; i++)
	{
		scanf("%d",&input[i]);
	}
	test(&input[0],&input[1],&input[2],&input[3],&input[4]);

}
