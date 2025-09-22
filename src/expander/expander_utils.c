/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:54:19 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/19 11:13:33 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_expander_in(t_data *data, char *line, char *expanded, int *start, int *end)
{
    int i;
    
    i = *start + 1;
    if (line[i] == '?')
    {
        if (expanded)
            expanded = ft_strjoin_f(expanded, ft_itoa(data->exit_status));       
        else
            expanded = ft_itoa(data->exit_status);
        *start = i; 
        *end = i + 1;  
    }
    
    return (expanded);
}
char *ft_get_sub(char *line, char *expanded, int start, int end)
{
    if (end > start)
    {
        if (expanded)
            expanded = ft_strjoin_f(expanded, ft_substr(line, start, end));
        else
            expanded = ft_substr(line, start, end);
    }
    return (expanded);
}
