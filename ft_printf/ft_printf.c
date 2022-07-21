/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:25:44 by joushin           #+#    #+#             */
/*   Updated: 2022/07/21 15:46:30 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include "./includes/libft.h"
#include<stdio.h>

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
	if (!args)
		return (-1);
	va_start(ap, args);
	while (*args)
	{
		if ((unsigned char)(*args) == '%')
		{
			args++;
			if (!infuc[(unsigned char)(*args)])
				cnt_tmp = write(1, args, 1);
			else
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
/*
%d하나만 있는 경우 우리 함수는 터진다. 하지만 원래 printf는 이걸 컴파일 자체가 불가능하게 만들었다.
%c인자에 문자열을 넣어도 원본 printf에서는 컴파일이 안된다.

*/
//int main()
//{
	// int a = 999;
	// char *p1 = "a";
	// char **p2 = &p1;
	// char ***p3 = &p2;
	// // printf("%d\n", printf("%p\n",p1));
	// // printf("%d\n", printf("%p\n",p2));
	// // printf("%d\n", printf("%p\n",p3));
	// // printf("%d\n", printf("%p\n",&a));
	// // printf("%d\n", printf("%p\n",NULL));
	// printf("my len :: %d\n",ft_printf("my printf ::%d, %d, %d, %d, %d, %d \n",1000,0,-6,2147483647,-2147364748,2147364748));
	// printf("or len :: %d\n",printf("or printf ::%d, %d, %d, %d, %d, %d \n",1000,0,-6,2147483647,-2147364748,2147364748));
	// printf("my len :: %d\n",ft_printf("my printf ::%i, %i, %i, %i, %i ,%i\n",1000,-6,10,2147483647,-2147364748,2147364748));
	// printf("or len :: %d\n",printf("or printf ::%i, %i, %i, %i, %i ,%i\n",1000,-6,10,2147483647,-2147364748,2147364748));
	// printf("my len :: %d\n",ft_printf("my printf ::%c %c %c %c %c %c\n",'a','a','\n','\0','0','l'));
	// printf("or len :: %d\n",printf("or printf ::%c %c %c %c %c %c\n",'a','a','\n','\0','0','l'));
	// printf("my len :: %d\n",ft_printf("my printf ::%p %p %p %p %p\n",p1,p2,p3,NULL,&a));
	// printf("or len :: %d\n",printf("or printf ::%p %p %p %p %p\n",p1,p2,p3,NULL,&a));
	// printf("my len :: %d\n",ft_printf("my printf ::%s %s %s %s\n","aaaaaaa","😎" ,"" ,NULL));
	// printf("or len :: %d\n",printf("or printf ::%s %s %s %s\n","aaaaaaa","😎" ,"" ,NULL));
	// printf("my len :: %d\n",ft_printf("my printf ::%u %u %u %u %u %u\n",1000,0,-6,2147483647,-2147364748,2147364748));
	// printf("or len :: %d\n",printf("or printf ::%u %u %u %u %u %u\n",1000,0,-6,2147483647,-2147364748,2147364748));
	// printf("my len :: %d\n",ft_printf("my printf ::%x %x %x %x %x %x %x\n",1000,0,100000,-12345,0,2147483647,2147364748));
	// printf("or len :: %d\n",printf("or printf ::%x %x %x %x %x %x %x\n",1000,0,100000,-12345,0,2147483647,2147364748));
	// printf("my len :: %d\n",ft_printf("my printf ::%X %X %X %X %X %X %X\n",1000,0,100000,-12345,0,2147483647,2147364748));
	// printf("or len :: %d\n",printf("or printf ::%X %X %X %X %X %X %X\n",1000,0,100000,-12345,0,2147483647,2147364748));
	// printf("my len :: %d\n",ft_printf("my printf ::%%\n"));
	// printf("or len :: %d\n",printf("or printf ::%%\n"));
	// printf("my len :: %d\n",ft_printf("my printf ::%m aaa\n"));
	// printf("or len :: %d\n",printf("or printf ::%m aaa\n"));
	//ft_printf("% %s\n","aaaa");
	//printf("% %s\n","aaa");
//}

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
