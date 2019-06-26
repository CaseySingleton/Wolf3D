/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:02:49 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/02 15:45:03 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include <stdio.h>

typedef struct			s_btree
{
	void				*data;
	struct s_btree		*left;
	struct s_btree		*right;
}						t_btree;

typedef struct			s_node
{
	void				*content;
	struct s_node		*next;
}						t_node;

typedef struct			s_stack
{
	struct s_node		*top;
}						t_stack;

typedef struct			s_queue
{
	struct s_node		*first;
	struct s_node		*last;
}						t_queue;

typedef struct			s_hash_data
{
	void				*data;
	int					key;
}						t_hash_data;

# define HASH_SIZE		257

/*
**	btree.c
*/

t_btree					*btree_new_node(void *data);
void					btree_rotate_clockwise(t_btree **node);

/*
**	stack.c
*/

t_stack					*stack_init(void);
void					*pop(t_stack *stack);
void					push(t_stack *stack, void *content);
void					*peek_stack(t_stack *stack);
int						is_stack_empty(t_stack *stack);

/*
**	queue.c
*/

t_queue					*queue_init(void);
void					enqueue(t_queue *queue, void *content);
void					*dequeue(t_queue *queue);
void					*peek_queue(t_queue *queue);
int						is_queue_empty(t_queue *queue);

/*
**	hash_table.c
*/

int						get_hash_code(int key);
void					hash_insert(void *data, t_hash_data **table);
t_hash_data				*hash_search(int key, t_hash_data **table);
void					hash_delete_item(t_hash_data *item, t_hash_data **table);
void					hash_print_item(int key, t_hash_data **table);

#endif
