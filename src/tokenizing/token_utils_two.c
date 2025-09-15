/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:23:22 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/07 22:30:59 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type ft_gettype_redir_or_pipe(char *line)
{
   
    if (!ft_strncmp(line, "<<", 2))
        return (T_HERODUC);
    else if (!ft_strncmp(line, "<", 1))
        return (T_IN_REDIR);
    else if (!ft_strncmp(line, ">>", 2))
        return (T_OUT_APP_REDIR);
    else if (!ft_strncmp(line, ">", 1))
        return (T_OUT_SUB_REDIR);
    else
        return (T_PIPE);    
}

char *ft_gettype_redir_value(t_type type)
{
    if (type == T_HERODUC)
        return (ft_strdup("<<"));
    if (type ==T_IN_REDIR)
        return (ft_strdup("<"));
    if (type ==T_OUT_APP_REDIR)
        return (ft_strdup(">>"));
    if (type == T_OUT_SUB_REDIR)
         return (ft_strdup(">"));
    else
        return (ft_strdup("|"));    
}

int ft_check_error(t_data *data, char c)
{
    if (c == '(' || c == ')')
    {
        data->error->msg = "error";
        return (1);
    }
    return (0);
}

void clear_token_other(void *to)
{
    t_token *token;

    token = (t_token *)to;
    if (!token)
        return ;
    free(token);
}
