/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:49:29 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/02 14:59:06 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_extarct_token(t_data *data, char **line)
{
    int i;
    char quote;

    printf("---- Entrei na funcao de extrair token ----\n");
    i = -1;
    quote = **line;
    while(*line && *line[++i])
    {
        if(*line[i] == quote)
            break;
    }
    if (*line[i] && data->token && data->token->value)
        ft_addargs_token(data->token, ft_substr(*line, 0, i + 1));
    else if(*line[i])
        ft_add_token(data, ft_substr(*line, 0, i + 1), T_COMAND);
    else
        return (0);
    *line += i;
    return (1);        
    
}


void ft_tokenizing(t_data *data, char *line)
{
    if (!line)
        return;

    while (*line)
    {
        
        ft_skipspace(&line);
        if (!*line)
            break;

        if (ft_isquote(*line))
        {
            if (ft_extarct_token(data, &line))
                ft_lstiter(data->list_token, print_token);
            continue;
        }
        else if (ft_isseparator(*line) && ft_isspace(*line))
        {
            printf("aqui entao\n");
            if (ft_extarct_token(data, &line))
                printf("--- After space separator --- a linha que sobrou e: %s\n", line);
            continue;
        }
        else if (ft_isseparator(*line) && is_redir_or_pipe(*line))
        {
            t_type type = ft_gettype_redir_or_pipe(line);
            ft_add_token(data, ft_substr(line, 0, (type == T_PIPE) ? 1 : 2), type);
            line += (type == T_PIPE) ? 1 : 2;
            continue;
        }
        line++;
    }
}
