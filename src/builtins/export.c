/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:05:46 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/23 10:37:09 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_export(void *en)
{
    t_env *env;
   
    env = (t_env *)en;
    if (!env)
        return ;
    printf("declare -x %s=\"%s\" \n",env->key, env->value);   
}

static int ft_is_valid_key(char *key)
{
    int i;

    i = -1;
    if (!key || !ft_isalpha(key[0]))
        return (0);
    while (key[++i] && key[i] != '=')
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
    }
    return (1);
}

int ft_export(t_data *data, char **args)
{
    int i;
    int j;
    char *key;
    char *value;
    
    if(!args[1])
        ft_lstiter(data->list_env, &print_export);
    j = 0;
    while (args[++j])
    {
        value = ft_strchr(args[j], '=');
        if (ft_is_valid_key(args[j]) && value)
        {
            i = ft_strlen(args[j]) - ft_strlen(value);
            key = ft_substr(args[j], 0, i);
            value = ft_substr(args[j] + (i + 1), 0, ft_strlen(args[j]));
            if (!ft_setenv_value(data, key, value))
                ft_add_env(data, ft_strdup(key), ft_strdup(value));
            (free(value), free(key));
        }
        else
        {
            ft_putstr_fd("-minishell : export: `", 2);
            ft_putstr_fd(args[j], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
        }
    }
    return (1);
}
