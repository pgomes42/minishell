/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:21:05 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/23 10:50:24 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_is_numeric(char *str)
{
    int i = 0;
    
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
    long result = 0;
    int sign = 1;
    int i = 0;
    
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
    {
        // Exit sem argumentos - usa exit_status atual
        exit(data->exit_status);
    }
    
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
    // Bash usa módulo 256 para exit codes
    exit((unsigned char)exit_code);
}

void ft_exit_f(t_data *data)
{
    (void)data;
    exit(0);
}