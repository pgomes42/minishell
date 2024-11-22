/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 05:38:33 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/21 05:38:34 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_del_aspas(char *str)
{
	size_t	i;
	int		s1len;
	char	*s1cpy;
	int		k;

	s1len = ft_strlen(str);
	s1cpy = ft_calloc(s1len + 1, sizeof(char));
	if (!s1cpy)
		return (NULL);
	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			continue ;
		}
		else
			s1cpy[k++] = str[i];
		i++;
	}
	s1cpy[k] = '\0';
	return (s1cpy);
}
