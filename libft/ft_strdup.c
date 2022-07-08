/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:36:35 by joushin           #+#    #+#             */
/*   Updated: 2022/07/08 14:41:22 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1);
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, s1, len + 1);
	return (result);
}
