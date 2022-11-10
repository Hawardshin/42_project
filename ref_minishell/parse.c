/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:33:20 by joushin           #+#    #+#             */
/*   Updated: 2022/11/07 20:16:43 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./include/shell.h"
#include "./include/parser.h"
#include "./include/scanner.h"
#include "./include/node.h"
#include "./include/source.h"
//개행을 얻을 때까지 tokenize함수를 계속해서 실행한다.
struct node_s   *parse_simple_command(struct token_s *tok)
{
    if(!tok)
    {
        return NULL;
    }
    
    struct node_s *cmd = new_node(NODE_COMMAND);
    if(!cmd)
    {
        free_token(tok);
        return NULL;
    }
    
    struct source_s *src = tok->src;
    do
    {
        if(tok->text[0] == '\n')
        {
            free_token(tok);
            break;
        }
        struct node_s *word = new_node(NODE_VAR);
        if(!word)
        {
            free_node_tree(cmd);
            free_token(tok);
            return NULL;
        }
        set_node_val_str(word, tok->text);
        add_child_node(cmd, word);
        free_token(tok);
    }while((tok = tokenize(src)) != &eof_token);
    return cmd;
}