/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:49:29 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/16 15:04:07 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_extarct_token(t_data *data, char **line, int *i)
{
    char *token;

    token = ft_substr(*line, 0, *i);
    if (!token)
        return ;
    if (ft_strlen(token) < 1)
        return ;
    if (data->token && data->token->value)
        ft_addargs_token(data->token, ft_strdup(token));
    else 
        ft_add_token(data, ft_strdup(token), T_COMAND);
    free(token);
    *line += *i;
    *i = -1;      
}
static int ft_extract_quote(t_data *data, char *line, int *pos, int quote)
{
    int i;
    bool find;

    find = false;
    i = quote;
    while (line[++i])
    {
        if (line[i] == line[quote])
        {
            find = true;
           break;
        }
    }
    *pos = i;
    if (!find)
        return (ft_parse_error(data, 2), 0);
    return (1);
}

static void ft_extract_redir(t_data *data, char **line, int *i)
{   
    t_type type;

    type = ft_gettype_redir_or_pipe(*(line) + *i);
    if(*i != 0)
        ft_extarct_token(data, line, i);
    ft_add_token(data, NULL, type);
   if (type == T_HERODUC || type== T_OUT_APP_REDIR)
        *line += 2;
    else
        *line += 1;
    *i = -1;
}

void ft_tokenizing(t_data *data, char *line)
{
    int i;

    i = -1;
    while (!ft_is_empty(line) && line[++i])
    {
        ft_skipspace(&line);
        if (ft_isquote(line[i]) && !ft_extract_quote(data, line, &i, i))
                break ;
        else if(ft_check_error(data, line[i]))
            return ; 
        else if (ft_isseparator(line[i]) && ft_isspace(line[i]))
            ft_extarct_token(data, &line, &i);
        else if (ft_isseparator(line[i]) && is_redir_or_pipe(line[i]))
           ft_extract_redir(data, &line, &i);
        else if(line[i + 1] == '\0' \
            && !ft_is_empty(line))
        {
            i++;
            ft_extarct_token(data, &line, &i);
            break ;
        }
    }
}
