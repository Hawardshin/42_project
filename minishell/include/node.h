/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:39:05 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 18:58:50 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
#define NODE_H
// AST 노드의 유형을 정의하는 enum 명령인지 변수인지. 
enum node_type_e
{
    NODE_COMMAND,
    NODE_VAR,
};
//주어진 노드 구조에 저장할 수 있는 값의 유형을 나타냅니다.
enum val_type_e
{
    VAL_SINT = 1,       /* signed int */
    VAL_UINT,           /* unsigned int */
    VAL_SLLONG,         /* signed long long */
    VAL_ULLONG,         /* unsigned long long */
    VAL_FLOAT,          /* floating point */
    VAL_LDOUBLE,        /* long double */
    VAL_CHR,            /* char */
    VAL_STR,            /* str (char pointer) */
};
//여차하면 struct로 바꾸기.
//주어진 노드 구조에 저장할 수 있는 값을 나타냅니다.
//각 노드는 문자열 또는 숫자 값과 같은 한 가지 유형의 값만 가질 수 있습니다. 
union symval_u
{
    long               sint;
    unsigned long      uint;
    long long          sllong;
    unsigned long long ullong;
    double             sfloat;
    long double        ldouble;
    char               chr;
    char              *str;
};
//AST 노드를 나타낸다.
//만약 이게 루트노드라면 children변수에는 총 자식 노드 갯수가 들어갈 것이고,
struct node_s
{
    enum   node_type_e type;    /* type of this node */
    enum   val_type_e val_type; /* type of this node's val field */
    union  symval_u val;        /* value of this node */
    int    children;            /* number of child nodes */
    struct node_s   *first_child; /* first child node */
    struct node_s   *next_sibling; //이중연결리스트 자식노드일때 해당.
    struct node_s   *prev_sibling; //이중연결리스트
                                /*
                                 * if this is a child node, keep
                                 * pointers to prev/next siblings
                                 */
};
struct  node_s *new_node(enum node_type_e type);
void    add_child_node(struct node_s *parent, struct node_s *child);
void    free_node_tree(struct node_s *node);
void    set_node_val_str(struct node_s *node, char *val);
#endif
