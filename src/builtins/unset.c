/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:18:55 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/23 09:40:31 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, char *args)
{
	t_env	*env;
	t_list	*list_env;
	t_list	*prev;

	prev = NULL;
	list_env = data->list_env;
	while (list_env)
	{
		env = (t_env *)list_env->content;
		if (!ft_strcmp(args, env->key))
		{
			clear_env((void *)env);
			if (prev)
				prev->next = list_env->next;
			else
				data->list_env = list_env->next;
			free(list_env);
			return (1);
		}
		prev = list_env;
		list_env = list_env->next;
	}
	return (0);
}
