/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:13:04 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/13 22:32:54 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_execute(t_data *data, t_ast *ast)
{
    if (!ast)
        return (1);
   (ft_execute(data, ast->left), ft_execute(data, ast->right));
    if (ast->type == T_COMAND && ft_is_builtin(ast->argv[0]))
        ft_execute_builtins(data, ast->argv);

return (1);
}