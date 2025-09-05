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

static void ft_extarct_token(t_data *data, char **line, int *i)
{
    if (data->token && data->token->value)
        ft_addargs_token(data->token, ft_substr(*line, 0, *i + 1));
    else 
        ft_add_token(data, ft_substr(*line, 0, *i + 1), T_COMAND);
    *line += *i;
    *i = -1;      
}
static int ft_extract_quote(t_data *data, char **line, int quote)
{
     int i;

    i = quote;
    while ((*line)[++i])
    {
        if ((*line)[i] == (*line)[quote])
            break;
    }
    if ((*line)[i] == (*line)[quote])
       ft_extarct_token(data, line, &i); 
    else
        return (0);
    return (1);
}

static void ft_extract_redir(t_data *data, char **line)
{   
    t_type type ;

    type = ft_gettype_redir_or_pipe(*line);
    ft_add_token(data, NULL, type);
   if (type == T_HERODUC || type== T_OUT_APP_REDIR)
        *line += 2;
    else
        *line += 1;     
}

void ft_tokenizing(t_data *data, char *line)
{
    int i;

    i = -1;
    while (line[++i])
    {
        ft_skipspace(&line);
        if (ft_isquote(line[i]))
        {
            if(!ft_extract_quote(data, &line, i))
                data->error = "\"";
        }
        else if(ft_check_error(data, line[i]))
            return ; 
        else if (ft_isseparator(line[i]) && ft_isspace(line[i]))
            ft_extarct_token(data, &line, &i);
        else if (ft_isseparator(line[i]) && is_redir_or_pipe(line[i]))
        {
           ft_extract_redir(data, &line);
            i = -1;   
        }
        else if(line[i + 1] == '\0' && !ft_isspace(line[i]))
        {
            ft_extarct_token(data, &line, &i);
            break;
        }
    }
}
