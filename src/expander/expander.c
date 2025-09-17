/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:10:33 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/16 15:15:51 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_get_sub(char *line, char *expanded, int start, int end)
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

static char *ft_remover_last(char *line, char *removed, int *start, int *last)
{
    int i;
    int j;

    i = *start;
    j = ++i;
    while (line[i] != line[*start])
        i++;
    removed = ft_get_sub(line, removed, j, i);
    *start = i;
    *last = i + 1;
    return (removed);
}

static char *ft_expand_env(t_data *data, char *argv[], int *start, int *last)
{
    int i;
    char *key;
    char *line;
    char *expanded;

    line = argv[0];
    expanded = argv[1];
    i = *start + 1;
    if (line[i] == '?')
    {
        if (expanded)
            expanded = ft_strjoin_f(expanded, ft_itoa(data->exit_status));       
        else
            expanded = ft_itoa(data->exit_status);
        *start = i;
        *last = i + 1;
        return (expanded);
    }
    while (line[i] && ft_isalnum(line[i]))
        i++;
    key = ft_substr(line, *start + 1, i);
    *start = i - 1;
    *last = i;
    if (expanded)
        expanded = ft_strjoin_f(expanded, ft_strdup(ft_getenv_value(data->list_env, key)));       
    else
        expanded = ft_strdup(ft_getenv_value(data->list_env, key));
    return (expanded); 
}

static char *expanded_double_quote(t_data *data, char *argv[], int *end, int *last)
{
   int  i;
   int j;
   char *line;
   char *expanded;

   line = argv[0];
   expanded = argv[1];
   i = *end;
   j = i + 1;
   while (line[++i] != '"')
    {
        if (line[i] == '$')
        {
            expanded = ft_get_sub(line, expanded, j, i);
            expanded = ft_expand_env(data, (char *[]){line, expanded}, &i, last);
        }
    }
    expanded = ft_get_sub(line, expanded, j, i);
    if (!expanded)
        expanded = ft_substr(line + j, 0, i);
    *end = i;
    *last = i + 1;
    return (expanded);
}

char *ft_expander(t_data *data, char *args)
{
    int i;
    int j;
    char *expanded;
   
    expanded = NULL;
    i = -1;
    j = 0;
    while (args && args[++i])
    {
        if (args[i] == '\'' || args[i] == '"' || args[i] == '$')
            expanded = ft_get_sub(args, expanded, j, i);
        if(args[i] == '\'')
            expanded = ft_remover_last(args, expanded, &i, &j);
        else if (args[i] == '"')
            expanded = expanded_double_quote(data, (char *[]){args, expanded}, &i, &j);
        else if (args[i] == '$')
            expanded = ft_expand_env(data, (char *[]){args, expanded}, &i, &j);
        if (args[i + 1] == '\0')
            break ;       
    }
    expanded = ft_get_sub(args, expanded, j, ++i);
    if (!expanded)
        expanded = ft_strdup(args);
    return (expanded); 
}

