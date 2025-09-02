/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:49:29 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/01 22:47:17 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_token_with_quote(t_data *data, char *line, int start, int *pos_curr)
{
    int i;
    char quote;

    i = *pos_curr;
    quote = line[i];
    while(line && line[++i])
    {
        if(line[i] == quote)
            break;
    }
    if (line[i] && data->token && data->token->value)
        ft_addargs_token(data->token, ft_substr(line, start, ++i));
    else if(line[i])
        ft_add_token(data, ft_substr(line, start, i ), T_COMAND);
    else
        return (0);
    *pos_curr = i; 
    return (1);        
    
}

static int  ft_separator_space(t_data *data, char *line, int start, int *pos_curr)
{
    int i;

    i = *pos_curr;
    if (line[i] && data->token && data->token->value)
        ft_addargs_token(data->token, ft_substr(line, start, ++i));
    else if(line[i])
        ft_add_token(data, ft_substr(line, start, i ), T_COMAND);
    start = ft_skipspace(line, &i);
    if (ft_isseparator(line[i]))
    {
        *pos_curr = i;
        return (0);        
    }

    while(line[++i])
    {
        if (ft_isquote(line[i]) && ft_token_with_quote(data, line, start, &i))
        {

        }
        else if(ft_isseparator(line[i]))
        {
            ft_addargs_token(data->token, ft_substr(line, start, i + 1));
            break;
        }   
    }
    *pos_curr = i;
    return (1);    
}

void ft_tokenizing(t_data *data, char *line)
{
    int i;
    int start;

    i = -1;
    while (line && line[++i])
    {
        start = ft_skipspace(line, &i);
        while (line && line[++i])
        {
            if (ft_isquote(line[i]) && ft_token_with_quote(data, line, start, &i))
            {               
                ft_lstiter(data->list_token, print_token);
            }
            else if (ft_isseparator(line[i]) && ft_isspace(line[i]) && ft_separator_space(data, line, start, &i))
            {
                 printf("ERROR\n");
            }
            
            
        }
        if(!line[i])
            break;
    }
    
}
