/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:21:46 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 13:26:26 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
#define SCANNER_H
struct  token_s
{
    struct source_s *src;       /* source of input */
    int             text_len;            /* length of token text */
    char            *text;               /* token text */
};
/* the special EOF token, which indicates the end of input */
struct token_s   eof_token; //전역변수 의미
struct token_s  *tokenize(struct source_s *src);
void            free_token(struct token_s *tok);
#endif 