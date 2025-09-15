/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:05:46 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/14 19:43:44 by pgomes           ###   ########.fr       */
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

int ft_export(t_data *data, char **args)
{
    int i;
    char *key;
    char *value;
    
    value = ft_strchr(args[1], '=');
    if(!args[1])
        ft_lstiter(data->list_env, &print_export);
    else if (ft_isalpha(args[1][0]) && value)
    {
        i = ft_strlen(args[1]) - ft_strlen(value + 1);
        key = ft_substr(args[1], 0, i);
        value = ft_substr(args[1] + (i + 1), 0, ft_strlen(args[1]));
        if (!ft_setenv_value(data, key, value))
            ft_add_env(data,  key, value);
        (free(value), free(key));
    }
    else
    {
        ft_putstr_fd("-minishell : export: `", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
    }
    return (1);
}
