/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:32:26 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 11:18:12 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char arr1[100] = {1, 0 , 2};
// 	char arr2[100] = {2 , 0 , 1};
// 	char arr3[100] = {1, 0 , 2};
// 	char arr4[100] = {2 , 0 , 1};
// 	char *arr5 = "abcabcabc";
// 	//char arr6[100] = {1,2,3,1,2,3,1,2,3};
// 	printf("%d\n\n",strncmp((char*)arr1,(char*)arr2,0));
// 	printf("%d\n\n",strncmp((char*)arr3,(char*)arr4,0));
// 	printf("%d\n\n",strncmp((char*)arr5,(char*)(arr5+2),10));
// 	printf("%d\n\n",strncmp((char*)(arr5+2),(char*)arr5,10));
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("%d\n\n",ft_strncmp((char*)arr1,(char*)arr2,0));
// 	printf("%d\n\n",ft_strncmp((char*)arr3,(char*)arr4,0));
// 	printf("%d\n\n",ft_strncmp((char*)arr5,(char*)(arr5+2),10));
// 	printf("%d\n\n",ft_strncmp((char*)(arr5+2),(char*)arr5,10));
// }
