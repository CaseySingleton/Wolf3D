/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 21:48:21 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/02 15:40:10 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_structs.h"

/*
**	A queue uses FIFO (first-in fist-out)
**	items are removed from the data structure in the same order that they
**	are added.
*/

/*
**	Initialize the queue. The first and last pointers are set to NULL.
*/

t_queue			*queue_init(void)
{
	t_queue		*new_queue;

	if (!(new_queue = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	new_queue->first = NULL;
	new_queue->last = NULL;
	return (new_queue);
}

/*
**	enqueue(queue, item) : Add an item to the end of the queue.
*/

void			enqueue(t_queue *queue, void *content)
{
	t_node		*new_node;

	if (!(new_node = (t_node *)malloc(sizeof(t_node))) || queue == NULL)
		return ;
	new_node->content = content;
	new_node->next = NULL;
	if (queue->first == NULL)
		queue->first = new_node;
	if (queue->last != NULL)
		queue->last->next = new_node;
	queue->last = new_node;
}

/*
**	dequeue(queue) : Remove the first item from the queue and return it.
**	If the queue is empty, the function returns NULL.
*/

void			*dequeue(t_queue *queue)
{
	t_node		*node;
	void		*content;

	content = NULL;
	if (queue != NULL && queue->first != NULL)
	{
		node = queue->first;
		content = node->content;
		queue->first = queue->first->next;
		free(node);
	}
	return (content);
}

/*
**	peek(queue) : Return the first item of the queue.
*/

void			*peek_queue(t_queue *queue)
{
	if (queue == NULL || queue->first == NULL)
		return (NULL);
	return (queue->first->content);
}

/*
**	isEmpty(queue) : Return 1 if the queue is empty, 0 otherwise.
*/

int				is_queue_empty(t_queue *queue)
{
	if (queue == NULL)
		return (-1);
	else if (queue->first == NULL)
		return (1);
	return (0);
}
