/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:07:06 by joushin           #+#    #+#             */
/*   Updated: 2022/11/11 22:08:55 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "node.h"

#define ENDOF -1 //널
#define CHAR 100
#define PIPE 101 // |
#define QUOTES 102 // ''
#define D_QUOTES 103 // ""
#define SPACE_B 104 // ' '
#define DOLLAR 105 // $
#define DIRECT 106 // <
#define RE_DIRECT 107 // >


t_token	*tokenize(t_readline *src);
char	see_char(t_readline *src);//보기만 함.
char	move_char(t_readline *src); //움직이기까지 함.

#endif
