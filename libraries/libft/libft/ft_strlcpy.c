/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:34:47 by pgomes            #+#    #+#             */
/*   Updated: 2024/07/31 13:02:06 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[len] != '\0' && len < size - 1)
	{
		dest[len] = src[len];
		len++;
	}
	if (len < size)
		dest[len] = '\0';
	return (ft_strlen(src));
}
