/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:07:31 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/04 21:39:19 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *get_env_value(t_list *list, char *key)
{
    t_list	*list_ptr;
    t_env *env;
    
	if (!list)
		return ;
	list_ptr = list;
	while (list_ptr != NULL)
	{
		env =(t_env *)list_ptr->content;
        if (env->key = key)
            return (env);
		list_ptr = list_ptr->next;
	} 
    return (NULL);
}
