/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:58:50 by joushin           #+#    #+#             */
/*   Updated: 2022/11/09 20:09:48 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

#include "node.h"

void	skip_white_spaces(t_readline *src);
char	see_char(t_readline *src);// 보기만 함.
char	move_char(t_readline *src);//움직이기까지 함.

#endif
