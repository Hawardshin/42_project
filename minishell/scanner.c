/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:30:26 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 21:30:16 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "./include/shell.h"
#include "./include/scanner.h"
#include "./include/source.h"
#include "./libft/libft.h"

/*

*/
char *tok_buf = NULL; //현재 토큰을 저장할 버퍼에 대한 포인터입니다.
int   tok_bufsize  = 0; //버퍼에 할당한 바이트 수입니다.
int   tok_bufindex = -1; //현재 버퍼 인덱스입니다(즉, 버퍼에서 다음 입력 문자를 추가할 위치를 알려줍니다).
/* special token to indicate end of input */
struct token_s eof_token = //파일/입력( EOF ) 의 끝을 알리는 데 사용할 특수 토큰 입니다.
{
    .text_len = 0,
};
 
void    add_to_buf(char c)// 토큰 버퍼에 단일 문자를 추가합니다. 버퍼가 가득 차면 함수가 확장을 처리합니다.
{
    char    *tmp;
    
    tok_buf[tok_bufindex++] = c;
    if (tok_bufindex >= tok_bufsize)
    {
        tmp = malloc(tok_bufsize *2);
        if (!tmp)
        {
            errno = ENOMEM;
            return ;
        }
        ft_memcpy(tmp, tok_buf, tok_bufindex);
        free(tok_buf);
        tok_buf = NULL; // 굳이?
        tok_buf = tmp;
        tok_bufsize *= 2;
    }
}
//토큰의 구조와 텍스트에 대한 메모리 할당을 처리하고 구조의 멤버 필드를 채웁니다.
//문자열을 가져와 struct token_s 구조로 변환하는 함수. 
struct token_s *create_token(char *str)
{
    struct token_s *tok = malloc(sizeof(struct token_s));

    if(!tok)
        return NULL;
    ft_memset(tok, 0, sizeof(struct token_s));
    tok->text_len = ft_strlen(str);
    
    char *nstr = malloc(tok->text_len+1);
    if(!nstr)
    {
        free(tok);
        return NULL;
    }
    strcpy(nstr, str);
    tok->text = nstr;
    
    return tok;
}
//토큰 구조에서 사용하는 메모리와 토큰의 텍스트를 저장하는 데 사용되는 메모리를 해제합니다.
void free_token(struct token_s *tok)
{
    if(tok->text)
    {
        free(tok->text);
    }
    free(tok);
}
//토큰 버퍼에 메모리를 할당하는 것으로 시작-> 토큰 버퍼와 소스 포인터를 초기화-> 다음 입력 문자를 검색하기 위해 next_char() 호출 -> 
//입력의 끝에 도달하면 입력 의 끝을 표시하는 eof token 을 반환한다. 그 후 한 번에 하나씩 입력 문자를 읽기 위해 루프하며 ->
// 공백 문자를 만나면 토큰 버퍼를 검사하여 비어 있는지 확인합니다. 버퍼가 비어 있지 않으면 현재 토큰을 구분하고 루프에서 벗어납니다. 
//그렇지 않으면 공백 문자를 건너뛰고 다음 토큰의 시작 부분으로 이동합니다.
struct token_s *tokenize(struct source_s *src)
{
    int endloop;

    endloop = 0;
    if(!src || !src->buffer || !src->bufsize)
    {
        errno = ENODATA;
        return &eof_token;
    }
    if(!tok_buf)
    {
        tok_bufsize = 1024;
        tok_buf = malloc(tok_bufsize);
        if(!tok_buf)
        {
            errno = ENOMEM;
            return &eof_token;
        }
    }
    tok_bufindex     = 0;
    tok_buf[0]       = '\0';
    char nc = next_char(src);
    if(nc == ERRCHAR || nc == EOF)
    {
        return &eof_token;
    }
    do
    {
        switch(nc)
        {
            case ' ':
            case '\t':
                if(tok_bufindex > 0)
                {
                    endloop = 1;
                }
                break;
                
            case '\n':
                if(tok_bufindex > 0)
                {
                    unget_char(src);
                }
                else
                {
                    add_to_buf(nc);
                }
                endloop = 1;
                break;
                
            default:
                add_to_buf(nc);
                break;
        }
        if(endloop)
        {
            break;
        }
    } while((nc = next_char(src)) != EOF);
    if(tok_bufindex == 0)
    {
        return &eof_token;
    }
    
    if(tok_bufindex >= tok_bufsize)
    {
        tok_bufindex--;
    }
    tok_buf[tok_bufindex] = '\0';
    struct token_s *tok = create_token(tok_buf);
    if(!tok)
    {
        ft_eprintf("error: failed to alloc buffer: %s\n", strerror(errno));
        return &eof_token;
    } 
    tok->src = src;
    return tok;
} 
