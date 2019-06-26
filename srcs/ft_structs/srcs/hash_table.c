/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:19:47 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/02 16:19:48 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_structs.h"

/*
**	Has errors. Especially calculating the hash code.
*/

int					get_hash_code(int key)
{
	return (key % HASH_SIZE);
}

void				hash_insert(void *data, t_hash_data **table)
{
	t_hash_data		*item;
	int				hash_index;

	if (!(item = (t_hash_data *)malloc(sizeof(t_hash_data))))
		return ;
	item->key = *((char *)data);
	item->data = data;
	hash_index = get_hash_code(item->key);
	while (table[hash_index] != NULL && table[hash_index]->key != -1)
	{
		hash_index++;
		hash_index %= HASH_SIZE;
	}
	table[hash_index] = item;
}

t_hash_data			*hash_search(int key, t_hash_data **table)
{
	int				hash_index;

	hash_index = get_hash_code(key);
	while (table[hash_index] != NULL)
	{
		if (table[hash_index]->key == key)
			return (table[hash_index]);
		hash_index++;
		hash_index %= HASH_SIZE;
	}
	return (NULL);
}

void				hash_delete_item(t_hash_data *item, t_hash_data **table)
{
	t_hash_data		*dummy;
	int				hash_index;

	hash_index = get_hash_code(item->key);
	while (table[hash_index] != NULL)
	{
		if (table[hash_index]->key == item->key)
		{
			if (!(dummy = (t_hash_data *)malloc(sizeof(t_hash_data))))
				return ;
			dummy->data = NULL;
			dummy->key = -1;
			free(table[hash_index]);
			table[hash_index] = dummy;
			return ;
		}
		hash_index++;
		hash_index %= HASH_SIZE;
	}
}

void				hash_print_item(int key, t_hash_data **table)
{
	t_hash_data		*item;

	if ((item = hash_search(key, table)) != NULL)
		printf("%s\n", item->data);
}	
