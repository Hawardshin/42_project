/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:38:18 by joushin           #+#    #+#             */
/*   Updated: 2022/07/07 13:09:15 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = b;
	while (i < len)
	{
		p[i] = c;
		i++;
	}
	return (b);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char arr[100];
// 	memset(arr,'a',10);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		printf("%d " ,arr[i]);
// 	}
// 	char arr1[100];
// 	ft_memset(arr1,'a',10);
// 	printf("\n------------------------after_--------------------\n");
// 	for (int i = 0;i < 100; i++)
// 	{
// 		printf("%d ",arr1[i]);
// 	}
// 	return (0);
// }
