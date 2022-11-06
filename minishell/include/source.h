/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorce.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:50:09 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 12:51:56 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
#define SOURCE_H
#define EOF             (-1)
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)
struct source_s
{   
    char    *buffer;       /* 입력 텍스트 */
    long    bufsize;       /* 입력 텍스트 크기*/
    long    curpos;       /* 소스 안에서 문자위치*/
};
char next_char(struct source_s *src);
void unget_char(struct source_s *src);
char peek_char(struct source_s *src);
void skip_white_spaces(struct source_s *src);
#endif 
