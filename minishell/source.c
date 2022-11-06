/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:52:39 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 21:30:27 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "./include/shell.h"
#include "./include/source.h"

//입력에서 검색한 마지막 문자를 다시 입력 소스로 반환
void    unget_char(struct source_s *src)
{
    if (src->curpos < 0)
    {
        return ;
    }
    src->curpos--;
}
//입력의 다음 문자를 반환하고 소스 포인터를 업데이트하여 다음에 대한 호출 next_char()이 다음 입력 문자를 반환하도록 합니다.
//입력의 마지막 문자에 도달하면 함수는 위에서 EOF를 반환합니다.

char    next_char(struct source_s *src)
{
    if(!src || !src->buffer)
    {
        errno = ENODATA;
        return (ERRCHAR);
    }
    char c1 = 0;
    if(src->curpos == INIT_SRC_POS)
    {
        src->curpos  = -1;
    }
    else
    {
        c1 = src->buffer[src->curpos];
    }
    if(++src->curpos >= src->bufsize)
    {
        src->curpos = src->bufsize;
        return EOF;
    }
    return (src->buffer[src->curpos]);
}

//next_char()입력의 다음 문자를 반환한다는 점에서 유사합니다. 
//유일한 차이점은 peek_char()소스 포인터를 업데이트하지 않으므로 다음에 대한 호출 next_char()이 방금 엿본 것과 동일한 입력 문자를 반환한다는 것입니다.
//즉 엿보기 함수.
char    peek_char(struct source_s *src)
{
    if (!src || !src->buffer)
    {
        errno = ENODATA;
        return (ERRCHAR);
    }
    long pos = src->curpos;
    if (pos == INIT_SRC_POS)
    {
        pos++;
    }
    pos++;
    if(pos >= src->bufsize)
    {
        return EOF;
    }
    return (src->buffer[pos]);
}
//모든 공백 문자를 건너뜁니다. 이것은 토큰 읽기를 마치고 다음 토큰을 읽기 전에 있는 공백을 모두 밀어줄 때 사용을 한다.
void skip_white_spaces(struct source_s *src)
{
    char c;
    if(!src || !src->buffer)
    {
        return;
    }
    while(((c = peek_char(src)) != EOF) && (c == ' ' || c == '\t'))
    {
        next_char(src);
    }
}