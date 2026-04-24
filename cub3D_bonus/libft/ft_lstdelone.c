/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:13:42 by vcastald          #+#    #+#             */
/*   Updated: 2024/12/18 11:00:38 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/*typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

void del(void *p)
{
	free(p);
}*/

void	ft_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	free(lst);
}

/*void stampa(t_list *list)
{
	while (list != NULL)
	{
		printf("%p\n", list->content);
		list = list->next;
	}
}

int main(void)
{
	t_list *head = NULL;
	t_list *new = NULL;

	new = malloc(sizeof(t_list));
	new->content = NULL;
	new->next = head;
	head = new;
	printf("Stampa prima di del: ");
	stampa(head);
	ft_lstdelone(new, del);
	printf("Stampa dopo del: ");
	stampa(head);
	return (0);
}*/
