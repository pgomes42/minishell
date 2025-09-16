/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:23:58 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/15 19:14:15 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void ft_update_pwd(t_data *data)
{
    char *str;
    
    str = ft_getenv_value(data->list_env, ft_strdup("PWD"));
    ft_setenv_value(data, "OLDPWD", str);
    str = getcwd(NULL, 0);
    ft_setenv_value(data, "PWD", str);
    free(str);
}
int ft_cd(t_data *data, char *argv[])
{
    char *str;

    if (argv[2])
        return (ft_putstr_fd("-minishell: cd: too many arguments \n", 2), 0);
    else if(!argv[1] && chdir(ft_getenv_value(data->list_env, ft_strdup("HOME"))) == 0)
        ft_update_pwd(data);
    else if (chdir(argv[1]) == 0)
        return (ft_update_pwd(data), 1);
    str = ft_strjoin("-minishell:  cd: ", argv[1]);
    perror(str);
    free(str);
    return (1);
}
