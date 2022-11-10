/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:16:02 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 19:16:40 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "node.h"
char    *search_path(char *file);
int     do_exec_cmd(int argc, char **argv);
int     do_simple_command(struct node_s *node);
#endif