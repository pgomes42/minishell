/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:23:22 by pgomes            #+#    #+#             */
/*   Updated: 2025/08/30 11:33:22 by pgomes           ###   ########.fr       */
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
