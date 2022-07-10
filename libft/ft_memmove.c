/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:55:46 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 07:32:52 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else if (d > s)
	{
		while (len--)
		{
			d[len] = s[len];
		}
	}
	return (dst);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char arr1[100] = "abcdefghijklmnop";
// 	char arr2[100] = "abcdefghijklmnop";
// 	memmove(arr1+3,arr1 ,55);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		printf("%c ",i,arr1[i]);
// 	}
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	ft_memmove(arr2+3,arr2,55);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		printf("%d%c ",i,arr1[i]);
// 	}
// }
