/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:12:29 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 21:21:19 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "./include/shell.h"
#include "./include/node.h"
#include "./include/parser.h"
//new_node()함수는 새 노드를 만들고 해당 type필드를 설정
struct node_s *new_node(enum node_type_e type)
{
    struct node_s *node = malloc(sizeof(struct node_s));
    if(!node)
    {
        return NULL;
    }
    
    memset(node, 0, sizeof(struct node_s));
    node->type = type;
    
    return (node);
}

//새 자식 노드를 추가하고 루트 노드의 children필드를 증가해서 심플 명령 ast를 확장한다.
void add_child_node(struct node_s *parent, struct node_s *child)
{
    if(!parent || !child)
    {
        return;
    }
    if(!parent->first_child)
    {
        parent->first_child = child;
    }
    else
    {
        struct node_s *sibling = parent->first_child;
    
    	while(sibling->next_sibling)
        {
            sibling = sibling->next_sibling;
        }
    
    	sibling->next_sibling = child;
        child->prev_sibling = sibling;
    }
    parent->children++;
}
//노드의 값을 주어진 문자열로 설정한다.
void set_node_val_str(struct node_s *node, char *val)
{
    node->val_type = VAL_STR;
    if(!val)
    {
        node->val.str = NULL;
    }
    else
    {
        char *val2 = malloc(strlen(val)+1);
    
    	if(!val2)
        {
            node->val.str = NULL;
        }
        else
        {
            strcpy(val2, val);
            node->val.str = val2;
        }
    }
}
// 노드 구조에서 사용하는 메모리를 해제합니다. 노드에 자식이 있으면 함수가 재귀적으로 호출되어 각각을 해제
void free_node_tree(struct node_s *node)
{
    if(!node)
    {
        return;
    }
    struct node_s *child = node->first_child;
    
    while(child)
    {
        struct node_s *next = child->next_sibling;
        free_node_tree(child);
        child = next;
    }
    if(node->val_type == VAL_STR)
    {
        if(node->val.str)
        {
            free(node->val.str);
        }
    }
    free(node);
} 