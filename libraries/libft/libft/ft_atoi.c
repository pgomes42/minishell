/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:27:34 by pgomes            #+#    #+#             */
/*   Updated: 2024/07/31 12:58:09 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_atoi(const char *str)
{
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str > 8 && *str < 14))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign *= -1;
		}
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}
