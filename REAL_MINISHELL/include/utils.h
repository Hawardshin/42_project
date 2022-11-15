/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:19:47 by joushin           #+#    #+#             */
/*   Updated: 2022/11/15 15:01:41 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "node.h"

void	my_free(void ** to_free);
char	*ft_mstrdup(const char *s1);
char	*ft_mstrjoin(char const *s1, char const *s2);
pid_t	mfork(void);
char	**ft_msplit(char *str, char c);
#endif
