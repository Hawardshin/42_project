/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:48:48 by joushin           #+#    #+#             */
/*   Updated: 2022/07/12 12:15:52 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				idx;
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	idx = 0;
	if (dst == src)
		return (dst);
	while (idx < n)
	{
		d[idx] = s[idx];
		idx++;
	}
	return (dst);
}
