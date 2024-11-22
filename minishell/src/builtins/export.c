/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:39:19 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/20 10:39:20 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_err_msg(char *identifier)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static void	ft_export_list(t_data *data)
{
	t_env	*list;
	size_t	i;

	list = data->envlst;
	while (list)
	{
		if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
		{
			printf("declare -x %s=\"", list->key);
			i = 0;
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					printf("\\%c", (list->value)[i++]);
				else
					printf("%c", (list->value)[i++]);
			}
			printf("\"\n");
		}
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

int	ft_check_key(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_data *data)
{
	int		exit_s;
	char	*key;
	t_token	*tmp;

	tmp = data->tokens->next;
	exit_s = 0;
	if (!tmp)
		return (ft_export_list(data), 0);
	while (tmp)
	{
		if (ft_check_key(tmp->value) == 0)
			exit_s = ft_export_err_msg(tmp->value);
		else
		{
			key = ft_extract_key(tmp->value);
			if (ft_env_entry_exists(data, key))
				ft_update_envlst(data, key, ft_extract_value(tmp->value),
					false);
			else
				ft_update_envlst(data, key, ft_extract_value(tmp->value), true);
		}
		tmp = tmp->next;
	}
	return (exit_s);
}
