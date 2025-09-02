/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:36:38 by pgomes            #+#    #+#             */
/*   Updated: 2025/08/30 16:13:50 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char *argv[], char *env[])
{
    t_data data;
  
    ft_memset(&data, 0, sizeof(data));
    if (argc > 1)
        return (perror("Execute minishel with no arguments!\n"), 1);
    (void)argv;
    (void)env;
    while (1)
    {
        data.line = readline("minishell$ ");
        if(data.line)
        {
            ft_tokenizing(&data, data.line);
            ft_lstiter(data.list_token, &print_token);
            ft_lstclear(&data.list_token, &clear_token);
            
        }
        
    }

    return (0);
}
