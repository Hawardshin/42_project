/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:10:31 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 21:48:31 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		++str;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (0);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	printf("%s",strchr("hi \0hellow \n",0)+1);
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("\n---------------after------------------\n");
// 	printf("%s",ft_strchr("hi \0hellow \n",0)+1);
// }
