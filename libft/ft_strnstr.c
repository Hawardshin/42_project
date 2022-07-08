/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 09:19:22 by joushin           #+#    #+#             */
/*   Updated: 2022/07/08 11:27:56 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	ni;

	i = 0;
	if (!ft_strlen(needle) || !needle[0])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		ni = 0;
		while (haystack[i + ni] && haystack[i + ni] == needle[ni]
			&& i + ni < len)
		{
			ni++;
			if (!needle[ni])
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	printf("result:%s\n",strnstr("abcdefabbccddee","abb",3));
// 	printf("result:%s\n",strnstr("abcdefabbccddee","abb",100));
// 	printf("result:%s\n",strnstr("abcdefabbccddee","abb",7));
// 	printf("result:%s\n",strnstr("abcdefabbccddee","abb",9));
// 	printf("result:%s\n",strnstr("abcdefabbccddee","",3));//NULL 인경우?
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("result:%s\n",ft_strnstr("abcdefabbccddee","abb",3));
// 	printf("result:%s\n",ft_strnstr("abcdefabbccddee","abb",100));
// 	printf("result:%s\n",ft_strnstr("abcdefabbccddee","abb",7));
// 	printf("result:%s\n",ft_strnstr("abcdefabbccddee","abb",9));
// 	printf("result:%s\n",ft_strnstr("abcdefabbccddee","",3));//NULL 인경우?

// }neddle이 haystack을
