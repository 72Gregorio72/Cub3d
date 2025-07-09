/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcastald <vcastald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:49:43 by vcastald          #+#    #+#             */
/*   Updated: 2025/07/03 14:41:08 by vcastald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		size;
	char	*dest;

	l1 = ft_strlen(s1);
	size = l1 + ft_strlen(s2) + 1;
	dest = (char *)malloc(size * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, size);
	ft_strlcat(dest, s2, size);
	return (dest);
}

/*int main(void)
{
    char *strs[] = {"Hello", "world", "from", "ChatGPT"};
    char *sep = "!";
    int size = sizeof(strs) / sizeof(strs[0]);

    char *result = ft_strjoin(size, strs, sep);
    if (result == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Joined string: '%s'\n", result);
    free(result); // Don't forget to free the allocated memory
    return 0;
}*/
