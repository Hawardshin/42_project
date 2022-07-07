/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:54:49 by joushin           #+#    #+#             */
/*   Updated: 2022/07/07 17:02:24 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d_len;

	d_len = ft_strlen(dst);
	i = 0;
	if (d_len < dstsize)
	{
		while (src[i] && d_len + i + 1 < dstsize)
		{
			dst[d_len + i] = src[i];
			i++;
		}
		dst[d_len + i] = '\0';
		return (ft_strlen(src) + d_len);
	}
	return (ft_strlen(src)+ dstsize);
}

#include<stdio.h>

#include<string.h>
int main()
{
	char d1[15] = "abcdefghi";
	char d2[15] = "abcdefghi";
	printf("%zu:::::\n\n",strlcat(d1,"ABCD",1));
	printf("%s:::::\n\n",d1);
	printf("%zu:::::\n\n",strlcat(d2,"KKKKKK",1000));
	printf("%s:::::\n\n",d1);
	printf("\n---------------after------------------\n");
	printf("\n---------------after------------------\n");
	printf("\n---------------after------------------\n");
	printf("\n---------------after------------------\n");
	char dd1[15] = "abcdefghi";
	char dd2[15] = "abcdefghi";
	printf("%zu:::::::\n\n",ft_strlcat(dd1,"ABCD",1));
	printf("%s:::::::\n\n",dd1);
	printf("%zu:::::::\n\n",ft_strlcat(dd2,"KKKKKK",1000));
	printf("%s:::::::\n\n",dd2);
}
