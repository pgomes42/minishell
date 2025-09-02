/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:13:22 by pgomes            #+#    #+#             */
/*   Updated: 2024/07/31 12:59:59 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest <= src || dest >= (src + n))
	{
		d = (unsigned char *)dest;
		s = (const unsigned char *)src;
		while (n--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		d = (unsigned char *)dest + n - 1;
		s = (const unsigned char *)src + n - 1;
		while (n--)
		{
			*d-- = *s--;
		}
	}
	return (dest);
}
