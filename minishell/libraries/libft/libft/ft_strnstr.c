/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:32:32 by pgomes            #+#    #+#             */
/*   Updated: 2024/07/31 13:02:06 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strnstr(const char *bus, const char *str, size_t size)
{
	size_t	len;

	len = ft_strlen(str);
	if (len == 0)
		return ((char *)bus);
	while (*bus && size >= len)
	{
		if (ft_strncmp(bus, str, len) == 0)
			return ((char *)bus);
		bus++;
		size--;
	}
	return (NULL);
}
