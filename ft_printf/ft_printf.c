/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:25:44 by joushin           #+#    #+#             */
/*   Updated: 2022/07/20 17:27:59 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_printf.h"

#include<stdio.h>

void	init_fuc_pointer(int (*fuc[256])(va_list ap))
{
	ft_memset(fuc, 0, 256);
	fuc['d'] = print_dec_int;
	fuc['i'] = print_dec_int;
	fuc['c'] = print_char;
	fuc['p'] = print_addr;
	fuc['s'] = print_str;
	fuc['u'] = print_unsigned_int;
	fuc['x'] = print_hex_lower;
	fuc['X'] = print_hex_upper;
	fuc['%'] = print_persent;
}

// int	va_print(char a, va_list ap, void *fuc[256])
// {
// 	int	*fut = fuc;
// 	fut[a](ap);
// }

int	ft_printf(const char *args, ...)
{
	va_list	ap;
	int		ret_cnt;
	int		i;
	int		(*fuc[256])(va_list ap);
	int		cnt_tmp;

	init_fuc_pointer(fuc);
	i = 0;
	ret_cnt = 0;
	if (!args)
		return (-1);
	va_start(ap, args);
	while (*args)
	{
		if (*args == '%')
		{
			args++;
			cnt_tmp = fuc[(unsigned char)(*args)](ap);
		}
		else
			cnt_tmp = write(1, args, 1);
		if (cnt_tmp == -1)
			break ;
		ret_cnt += cnt_tmp;
		args++;
	}
	va_end(ap);
	if (cnt_tmp < 0)
		return (-1);
	return (ret_cnt);
}

int main()
{
	ft_printf("hi\n%%\n%d\n%d\n",1 ,2);
}

// #include <stdio.h>
// int test(int *ar, int a, ...)
// {
// 	va_list ap;
// 	va_start(ap, ar);
// 	//printf("000::: %p\n",ap);
// 	for (int i =0; i < 12; i++)
// 	{
// 		printf("%p\n",ap);
// 		//printf("ar:::::: %d,%p\n",*ar ,ar);
// 		printf("%d\n", va_arg(ap,int));
// 		//ap += sizeof(int);
// 	}
// 	int result = 0;
// 	va_end(ap);
// 	return (0);
// }
// int main()
// {
// 	// char* value = "asdf";
// 	// unsigned char *p= (unsigned char*)&value;
// 	// char *hex = "0123456789abcdef";
// 	// for (int i = 7; i >= 0; i--)
// 	// {
// 	// 	write(1, &hex[p[i] / 16], 1);
// 	// 	write(1, &hex[p[i] % 16], 1);
// 	// }
// 	// write(1, "\n", 1);
// 	// printf("%p\n", value);
// 	int input[6];
// 	int a[6];
// 	for (int i= 0; i< 5; i++)
// 	{
// 		scanf("%d %d",&input[i], &a[i]);
// 	}
// 	test(&input[0],a[0],input[1],a[1],input[2],a[2],input[3],a[3],input[4],a[4]);
// }
