/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:36:38 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/04 21:25:14 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
static void ft_init(t_data *data, char **env)
{
    ft_extrat_env(data, env);
     ft_lstiter(data->list_env, &print_env);
}
int main(int argc, char *argv[], char *env[])
{
    t_data data;
  
    ft_memset(&data, 0, sizeof(data));
    if (argc > 1)
        return (perror("Execute minishel with no arguments!\n"), 1);
    (void)argv;
     ft_init(&data, env);
    while (0)
    {   
        data.line = readline("minishell$ ");
        if(data.line)
        {
            if(data.line[0])
                add_history(data.line);
            ft_tokenizing(&data, data.line);
            if(data.error)
                (ft_lstclear(&data.list_token, &clear_token), ft_memset(&data, 0, sizeof(data)));
            ft_lstiter(data.list_token, &print_token);
            (ft_lstclear(&data.list_token, &clear_token), 
            free(data.line), ft_memset(&data, 0, sizeof(data))); 
        }
        else
            exit(data.status); 
    }
    return (0);
}
