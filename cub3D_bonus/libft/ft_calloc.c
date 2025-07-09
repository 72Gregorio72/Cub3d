/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:38:04 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/03 14:38:07 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, (size * nmemb));
	return (dest);
}
