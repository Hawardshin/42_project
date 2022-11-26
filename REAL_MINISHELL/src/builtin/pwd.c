/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:08:21 by tson              #+#    #+#             */
/*   Updated: 2022/11/26 19:22:12 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
