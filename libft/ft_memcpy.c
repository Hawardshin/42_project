/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:48:48 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 07:31:58 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (dst == src)
		return (dst);
	while (n--)
		*d++ = *s++;
	return (dst);
}
// #include<stdio.h>

// #include<string.h>
// int main()
// {
// 	char arr1[100];
// 	char arr2[100];
// 	memcpy(arr1,"hi I am joushin",0);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		printf("%d ",arr1[i]);
// 	}
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	ft_memcpy(arr2,"hi I am joushin",0);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		printf("%d ",arr2[i]);
// 	}
// }
