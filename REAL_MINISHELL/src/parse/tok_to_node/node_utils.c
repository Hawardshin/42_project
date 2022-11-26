/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:47:50 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 16:28:44 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

static char	*ft_make_cmd_path(t_main_node *px, char *text, int i)
{
	char	*tmp;
	char	*ptmp;

	tmp = ft_mstrjoin("/", text);
	ptmp = ft_mstrjoin(px->path[i], tmp);
	my_free((void **) &tmp);
	return (ptmp);
}

static char	*ft_make_relative_path(char *text)
{
	char	*tmp;
	char	*p;
	int		i;

	p = getcwd(NULL, 0);
	i = 0;
	if (p == NULL)
		print_error(0, NULL);
	if (ft_strncmp(text, "./", 2) == 0)
		tmp = ft_mstrjoin(p, text + 1);
	else
	{
		while (p[i])
			i++;
		i--;
		while (i > 0 && p[i] != '/' )
			i--;
		p[i] = '\0';
		tmp = ft_mstrjoin(p, text + 2);
	}
	free(p);
	return (tmp);
}

char	*find_path(char *text, t_main_node *main_node)
{
	int			i;
	char		*ptmp;
	struct stat	st;

	i = -1;
	if (!main_node->path)
		return (NULL);
	while (main_node -> path[++i])
	{
		if (ft_strncmp(text, "./", 2) == 0 || ft_strncmp(text, "../", 3) == 0)
		{
			ptmp = ft_make_relative_path(text);
		}
		else if (ft_strncmp(text, "/", 1) != 0)
			ptmp = ft_make_cmd_path(main_node, text, i);
		else
			ptmp = ft_mstrdup(text);
		if (stat(ptmp, &st) == 0)
			return (ptmp);
		my_free((void **)&ptmp);
	}
	return (NULL);
}

static void	make_hdoc_node_utils(t_node *node, \
			t_infile_node **infile, t_token **tmp_tok)
{
	t_infile_node	*itmp;

	if ((node->infile_node) == NULL)
		node->infile_node = (*infile);
	else
	{
		itmp = node->infile_node;
		while (itmp->next != NULL)
			itmp = itmp->next;
		itmp->next = (*infile);
		(*infile)->prev = itmp;
	}
	(*tmp_tok) = (*tmp_tok)->next;
	(*infile)->file = ft_mstrdup((*tmp_tok)->text);
	(*infile)->is_heardoc = 1;
}

void	make_hdoc_node(t_node *node, t_token **tmp_tok)
{
	t_infile_node	*infile;
	t_infile_node	*itmp;

	infile = malloc(sizeof (t_infile_node));
	if (!infile)
		print_error(0, NULL);
	ft_memset(infile, 0, sizeof(t_infile_node));
	make_hdoc_node_utils(node, &infile, tmp_tok);
	if ((node->heardoc_node) == NULL)
		node->heardoc_node = infile;
	else
	{
		itmp = node->heardoc_node;
		while (itmp->hnext != NULL)
			itmp = itmp->hnext;
		itmp->hnext = infile;
		infile->hprev = itmp;
	}
}
