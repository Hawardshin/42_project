/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:57:13 by tson              #+#    #+#             */
/*   Updated: 2022/11/26 13:13:25 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
#include "node.h"

int		cmd_len(char **cmd);
void	ft_cd(char **cmd, int flag);
void	ft_echo(char **cmd);
void	print_sorted_env(char *format);
void	print_normal_env(char *format);
void	ft_env(int is_sort, char *format);
void	ft_exit(char	**cmd);
char	*set_key(char *str);
char	*set_value(char *str);
void	input_env(char *str);
void	ft_export(char **cmd);
void	ft_pwd();
void	ft_unset(char **cmd);
int		ft_in_built(t_node *val, int flag);
int		ft_built_check(char *str);
int		ft_built_first_check(char *str);
#endif
