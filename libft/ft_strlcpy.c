/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:30:30 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 08:54:11 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i + 1 < dstsize)
	{
		if (src[i])
		{
			dst[i] = src[i];
			i++;
		}
		else
			break ;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// #include<stdio.h>
// #include<string.h>

// int main()
// {
// 	char dst1[100]={'a'};
// 	char dst2[100]={'a'};
// 	size_t len1 = strlcpy(dst1, "this is joushin",0);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		printf("%d ",dst1[i]);
// 	}
// 	printf("\n\nlen ::::::: %zu\n\n",len1);
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	size_t len2 = ft_strlcpy(dst2, "this is joushin",0);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		printf("%d ",dst2[i]);
// 	}
// 	printf("\n\nlen ::::::: %zu\n\n",len2);
// }
