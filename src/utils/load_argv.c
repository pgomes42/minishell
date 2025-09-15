/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:39:41 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/14 18:42:29 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_load_env_argv(t_data *data)
{
    t_list *list_env;
    t_env *env;
    int size;
    char *str;
   
   size = ft_lstsize(data->list_env);
   data->argv_env = (char **)malloc(sizeof(char *) * (size + 2));
   list_env = data->list_env;
   size = 0;
   while (list_env)
   {
        env = (t_env *)list_env->content;
        str = ft_strjoin(env->key, "=");
        str = ft_strjoin_f(str, ft_strdup(env->value));
        data->argv_env[size] = str;
        size++;
        list_env = list_env->next;
   }
   data->argv_env[size] = NULL;   
}

void ft_load_ats_argv(t_data *data, t_ast *ast)
{
   int i;

    if (!ast)
        return ;
    ft_load_ats_argv(data, ast->left);
    ft_load_ats_argv(data, ast->right);
    if (ast->type != T_PIPE)
    {
        ast->argv = (char **)malloc(sizeof(char *) * (ast->nb_args + 2));
        if (!ast->argv)
            perror("Argv");
        ast->argv[0] = ft_expander(data, ast->value);
        ast->argv[ast->nb_args + 1] = NULL;
        i = -1;     
        while (ast->args && ast->args[++i])
            ast->argv[i + 1] = ft_expander(data, ast->args[i]);
       
    }
}