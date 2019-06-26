/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 22:25:29 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/04 22:25:30 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_structs.h"

t_btree				*btree_new_node(void *data)
{
	t_btree			*new_btree;

	if (!(new_btree = (t_btree *)malloc(sizeof(t_btree))))
		return (NULL);
	new_btree->data = data;
	new_btree->left = NULL;
	new_btree->right = NULL;
	return (new_btree);
}

void				btree_rotate_clockwise(t_btree **node)
{
	t_btree			*tree;
	t_btree			*left;

	tree = *node;
	if (tree == NULL || tree->left == NULL || tree->left->left != NULL)
		return ;
	tree = tree->left;
}
