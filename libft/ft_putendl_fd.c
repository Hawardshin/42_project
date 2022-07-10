/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 06:48:29 by joushin           #+#    #+#             */
/*   Updated: 2022/07/11 06:49:19 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n',fd);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	ft_putendl_fd("hi my name is joushin", 1);

// 	// printf("\n---------------after------------------\n");
// 	// printf("\n---------------after------------------\n");
// 	// printf("\n---------------after------------------\n");
// 	// printf("\n---------------after------------------\n");

// }
