/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tson <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:08:21 by tson              #+#    #+#             */
/*   Updated: 2022/11/23 16:23:43 by tson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"

void	ft_pwd()
{
	char	*p;

	p = getcwd(NULL, 0);
	if (p == NULL)
		print_error(0, NULL);
	printf("%s\n", p);
	free(p);
}