/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:21:05 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/23 11:34:15 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_is_numeric(char *str)
{
    int i;
    
    i = 0;
    if (!str || !*str)
        return (0);
    if (str[0] == '+' || str[0] == '-')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static long ft_atol(char *str)
{
    long result;
    int sign;
    int i; 
    
    result = 0;
    sign = 1;
    i = 0;
    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[0] == '+')
        i++;
    while (str[i])
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

int ft_exit(t_data *data, char **argv)
{
    long exit_code;
    
    ft_putstr_fd("exit\n", 1);
    if (!argv[1])
        exit(data->exit_status);    
    if (!ft_is_numeric(argv[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(argv[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        exit(2);
    }
    if (argv[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
    }
    exit_code = ft_atol(argv[1]);
    exit((unsigned char)exit_code);
}
