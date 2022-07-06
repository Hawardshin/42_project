/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:03:18 by joushin           #+#    #+#             */
/*   Updated: 2022/07/06 18:56:39 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = 0;
}

// #include<string.h>
// #include<stdio.h>
// int main()
// {
// 	char arr1[100];
// 	char arr2[100];
// 	bzero(arr1,100);
// 	for (int i= 0; i < 100; i++)
// 	{
// 		printf("%d ",arr1[i]);
// 	}
// 	printf("\n------------after-------------\n");
// 	ft_bzero(arr2,100);
// 	for (int i= 0; i < 100; i++)
// 	{
// 		printf("%d ",arr2[i]);
// 	}
// }
