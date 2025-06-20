/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:10:24 by vcastald          #+#    #+#             */
/*   Updated: 2024/11/26 09:10:50 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

/*void stampa(t_list *ptr)
{
	while (ptr != NULL)
	{
		printf("%d\n", ptr->content);
		ptr = ptr->next;
	}
}

int main(void)
{
	t_list *head = NULL;
	t_list *new = NULL;
	t_list *test = NULL;
	t_list **ptr;

	for (int i = 0; i < 10; i++)
	{
		new = malloc(sizeof(t_list));
		new->content = i;
		new->next = head;
		head = new;
	}
	ptr = &head;
	test = malloc(sizeof(t_list));
	test->content = NULL;
	test->next = NULL;
	ft_lstadd_front(ptr, test);
	stampa(test);
	return (0);
}*/
