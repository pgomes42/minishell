/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:10:33 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/23 10:42:35 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_find_last(char *line,char *expanded, int *start, int *last)
{
    int i;

    i = *start + 1;
    while (line[i] != line[*start])
        i++;
    expanded = ft_get_sub(line, expanded, *start + 1, i);
    *start = i;
    *last = i + 1;
    return (expanded);
}

static char *ft_expand_env(t_data *data, char *argv[], int *start, int *last)
{
    int i;
    char *key;
    char *line;
    char *expanded;

    line = argv[0];
    i = *start + 1;
    expanded = argv[1];
    while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
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

static char *expanded_quote(t_data *data, char *argv[], int *start, int *last)
{
   int  i;
   int j;

   if (argv[0][*start] == '\'')
   {
       argv[1] = ft_find_last(argv[0], argv[1], start, last);
        return (argv[1]);
    }
   i = *start;
   j = i + 1;
   while (argv[0][++i] != '"')
    {
        if (argv[0][i] == '$' && (argv[0][i + 1] == '?' || ft_isalnum(argv[0][i + 1])))
            argv[1] = ft_get_sub(argv[0], argv[1], j, i);
        if (argv[0][i] == '$' && argv[0][i + 1] == '?')
            argv[1] = ft_expander_in(data, argv[0], argv[1], &i, &j);
        if (argv[0][i] == '$' && ft_isalnum(argv[0][i + 1]))
            argv[1] = ft_expand_env(data, (char *[]){argv[0], argv[1]}, &i, &j);
    }
    argv[1] = ft_get_sub(argv[0], argv[1], j, i);
    if (!argv[1])
        argv[1] = ft_substr(argv[0], j, i);
    *start = i;
    *last = i + 1;
    return (argv[1]);
}

char *ft_expande_heroduc(t_data *data, char *line)
{
    char *expande;
    int i;
    int j;

    expande = NULL;
    i = -1;
    j = 0;
    while (line && line[++i])
    {
        if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
            expande = ft_get_sub(line, expande, j, i);
        if (line[i] == '$' && line[i] == '?')
            expande = ft_expander_in(data, line, expande, &i, &j);
        else if (line[i] == '$' && ft_isalnum(line[i + 1]))
            expande = ft_expand_env(data, (char *[]){line, expande}, &j, &i);
    }
    expande = ft_get_sub(line, expande, j, i);
    free(line);
    return (expande);
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
        if (args[i] == '"' || args[i] == '\'' 
            || (args[i] == '$' && (ft_isalnum(args[i + 1]) || args[i + 1] == '?')))
            expanded = ft_get_sub(args, expanded, j, i);
        if(args[i] == '$' && args[i + 1] == '?')  
            expanded = ft_expander_in(data, args, expanded, &i, &j);
        else if (args[i] == '"' || args[i] == '\'')
            expanded = expanded_quote(data, (char *[]){args, expanded}, &i, &j);
        else if (args[i] == '$' && ft_isalnum(args[i + 1]))
            expanded = ft_expand_env(data, (char *[]){args, expanded}, &i, &j);
        if (args[i + 1] == '\0')
            break ;       
    }
    if (!expanded)
        expanded = ft_strdup(args);
    return (expanded); 
}