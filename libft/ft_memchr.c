/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:41:28 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 07:25:40 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	str = s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *) &str[i]);
		i++;
	}
	return (0);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	//char *result = memchr("ab\0cdefg",0,10);
// 	char *result = memchr("NULL",0,10);
// 	printf("%s",result+1);
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	char *result2 = ft_memchr("NULL",0,10);
// 	printf("%s",result2+1);
// }
