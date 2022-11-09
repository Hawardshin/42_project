/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:08:51 by joushin           #+#    #+#             */
/*   Updated: 2022/11/09 22:27:34 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_UTILS_H
# define M_UTILS_H

# include "node.h"

void	my_free(char **to_free);
char	*ft_mstrdup(const char *s1);
char	*ft_mstrjoin(char const *s1, char const *s2);

pid_t	mfork(void);

#endif
