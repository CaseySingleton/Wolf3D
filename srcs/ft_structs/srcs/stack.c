/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:47:08 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/02 15:47:09 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_structs.h"

/*
**	A stack uses LIFO (last-in fist-out) the most recent item added to the
**	stack is the first item to be removed.
*/

/*
**	Initialize the stack.
*/

t_stack				*stack_init(void)
{
	t_stack			*new_stack;

	if (!(new_stack = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	new_stack->top = NULL;
	return (new_stack);
}

/*
**	Remove the top item from the stack and return it. If the stack is empty,
**	the function returns NULL.
*/

void				*pop(t_stack *stack)
{
	t_node			*next;
	void			*content;

	content = NULL;
	next = NULL;
	if (stack != NULL && stack->top != NULL)
	{
		next = stack->top->next;
		content = stack->top->content;
		free(stack->top);
		stack->top = next;
	}
	return (content);
}

/*
**	Add an item to the top of the stack.
*/

void				push(t_stack *stack, void *content)
{
	t_node			*new_node;

	if (!(new_node = (t_node *)malloc(sizeof(t_node))) || stack == NULL)
		return ;
	new_node->content = content;
	new_node->next = stack->top;
	stack->top = new_node;
}

/*
**	Return the top of the stack.If the stack is empty, the function
**	returns NULL.
*/

void				*peek_stack(t_stack *stack)
{
	if (stack != NULL && stack->top != NULL)
		return (stack->top->content);
	return (NULL);
}

/*
**	Return 1 if the stack is empty, 0 otherwise.
*/

int					is_stack_empty(t_stack *stack)
{
	if (stack == NULL)
		return (-1);
	else if (stack->top == NULL)
		return (1);
	return (0);
}
