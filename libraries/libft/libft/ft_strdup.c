/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:43:47 by pgomes            #+#    #+#             */
/*   Updated: 2024/07/31 13:02:06 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strdup(const char *src)
{
	char	*string;
	int		src_size;
	int		i;

	i = 0;
	src_size = ft_strlen(src);
	string = (char *)malloc(sizeof (*string) * (src_size + 1));
	while (i < src_size)
	{
		string[i] = src[i];
		i++;
	}
	string[src_size] = '\0';
	return (string);
}
