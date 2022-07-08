/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:14:25 by joushin           #+#    #+#             */
/*   Updated: 2022/07/08 19:39:32 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (start > slen)

	str[i] = '\0';
	return (str);
}
//1. 예외 1 : start값보다 문자열의 길이가 짧은경우 return 크기 1짜리인 프리할 수 있는 널이 들어간 문자열
//2. 예외 2 : 만약 len값이 s의 길이보다 짧다면 길이를 끝까지 조정한다?
