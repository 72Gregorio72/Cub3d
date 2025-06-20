/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:09:10 by vcastald          #+#    #+#             */
/*   Updated: 2025/01/22 10:52:13 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*d;

	d = (t_list *)malloc(sizeof(t_list));
	if (!d)
		return (NULL);
	d->content = content;
	d->index = 0;
	d->next = NULL;
	return (d);
}

/*typedef struct s_list
{
	void *content;
	struct s_list *next;
}		t_list;


void stampa(t_list *list)
{
	while (list != NULL)
	{
		printf("%d", list->content);
		list = list->next; 
	}
}

int main(void)
{
	int i = 0;
	t_list *d;

	while (i < 10)
	{
		d = ft_lstnew((void *)i);
		i++;
	}
	stampa(d);
	return (0);
}*/
