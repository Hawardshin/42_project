/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:08:21 by tson              #+#    #+#             */
/*   Updated: 2022/11/26 15:42:17 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"

void	ft_pwd(void)
{
	char	*p;

	p = getcwd(NULL, 0);
	if (p == NULL)
		print_error(0, NULL);
	printf("%s\n", p);
	free(p);
}
