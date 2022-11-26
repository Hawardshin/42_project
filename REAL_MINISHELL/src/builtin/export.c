/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:01:47 by tson              #+#    #+#             */
/*   Updated: 2022/11/26 19:21:35 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../libft/libft.h"
#include "../../include/builtin.h"

static char	*set_key(char *str)
{
	int		equal_idx;
	char	*ret;

	equal_idx = ft_strchr(str, '=') - str;
	if (ft_strchr(str, '=') == NULL)
		equal_idx = ft_strlen(str);
	ret = ft_substr(str, 0, equal_idx);
	if (ret == NULL)
		print_error(0, NULL);
	if (ft_strcmp(ret, "") == 0)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}

static char	*set_value(char *str)
{
	int		equal_idx;
	char	*ret;

	if (ft_strchr(str, '=') == NULL)
		return (0);
	equal_idx = ft_strchr(str, '=') - str;
	ret = ft_substr(str, equal_idx + 1, ft_strlen(str) - (equal_idx + 1));
	if (ret == NULL)
		print_error(0, NULL);
	return (ret);
}

static void	input_env(char *str)
{
	char	*key;
	char	*value;

	key = set_key(str);
	value = set_value(str);
	if (key == NULL || ft_strchr(key, '-'))
	{
		ft_eprintf("minishell: export: `%s': not a valid identifier\n", str);
		return ;
	}
	env_lst_add_back(key, value);
}

void	ft_export(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		input_env(cmd[i]);
		i++;
	}
	if (i == 1)
		ft_env(1, "declare -x ");
}
