/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:23:22 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/04 21:58:58 by pgomes           ###   ########.fr       */
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

int ft_check_error(t_data *data, char c)
{
    if (c == '(' || c == ')')
    {
        data->error = "error";
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
