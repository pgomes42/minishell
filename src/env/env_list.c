/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:48:17 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/13 23:43:28 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env *ft_newenv(char *key, char *value)
{
    t_env *env;
    
    env = (t_env *)malloc(sizeof(t_env));
    if (!env)
        return (perror("Falied to creat envoiriment"), NULL);
    env->key = key;
    env->value = value;
    return (env);
}

void clear_env(void *en)
{
    t_env *env;
  
    env = (t_env *)en;
    if (!env)
        return ;
    if (env->value)
        free(env->value);
    if (env->key)
        free(env->key);
    free(env);
}

void print_env(void *en)
{
    t_env *env;
   
    env = (t_env *)en;
    if (!env)
        return ;
    printf("%s=%s \n",env->key, env->value);   
}

int ft_add_env(t_data *data, char *key, char *value)
{
    t_env *env;
    
    env = ft_newenv(key, value);
    if(!env)
        return (0);
    if(!data->list_env)
        data->list_env = ft_lstnew(env);
    else
        ft_lstadd_back(&data->list_env, ft_lstnew(env));
    return (1);
}
int ft_setenv_value(t_data *data, char *key, char *value)
{
    t_list *temp;
    t_env   *env;
    
    temp = data->list_env;
    while (temp)
    {
        env = (t_env *)temp->content;
        if (!ft_strcmp(env->key, key))
        {
            free(env->value);
            env->value = ft_strdup(value);
            return (1);
        }   
        temp = temp->next;
    }
    return (0);
}

char *ft_getenv_value(t_list *list, char *key)
{
    t_list *temp;
    t_env   *env;
    char    *value;
    
    value = "";
    temp = list;
    while (temp)
    {
        env = (t_env *)temp->content;
        if (!ft_strcmp(env->key, key))
            return (env->value); 
        temp = temp->next;
    }
    free(key);
    return (value);
}

void ft_extrat_env(t_data *data, char **env)
{
    int i;
    int j;

    i = -1;
    while (env && env[++i])
    {
        j = -1;
        while (env[i][++j])
        {
            if (env[i][j] == '=' && ft_add_env(data, ft_substr(env[i], 0, j),
             ft_substr(env[i], j + 1, ft_strlen(env[i]))))
                break;     
        }
        
    }
}
