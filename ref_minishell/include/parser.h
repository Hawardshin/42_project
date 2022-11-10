/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:31:04 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 18:31:28 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H
#include "scanner.h"    /* struct token_s */
#include "source.h"     /* struct source_s */
struct node_s *parse_simple_command(struct token_s *tok);
#endif