/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:23:58 by pgomes            #+#    #+#             */
/*   Updated: 2025/10/01 11:37:29 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_pwd(t_data *data)
{
	char	*str;

	str = ft_getenv_value(data->list_env, ft_strdup("PWD"));
	if (!ft_setenv_value(data, "OLDPWD", str))
		ft_add_env(data, ft_strdup("OLDPWD"), ft_strdup(str));
	str = getcwd(NULL, 0);
	ft_setenv_value(data, "PWD", str);
	free(str);
}

static int	ft_cd_back(t_data *data)
{
	char	*str;

	str = ft_getenv_value(data->list_env, ft_strdup("OLDPWD"));
	if (ft_is_empty(str))
		return (ft_putstr_fd("-minishell: cd: OLDPWD not set\n", 2), 0);
	if (chdir(str) == 0)
		return (printf("%s\n", str), ft_update_pwd(data), 1);
	str = ft_strjoin("-minishell:  cd: ", str);
	perror(str);
	free(str);
	return (0);
}

int	ft_cd(t_data *data, char *argv[])
{
	char	*str;

	if (argv[2])
		return (ft_putstr_fd("-minishell: cd: too many arguments \n", 2), 0);
	else if (!argv[1] && chdir(ft_getenv_value(data->list_env,
				ft_strdup("HOME"))) == 0)
		ft_update_pwd(data);
	else if (!ft_strcmp(argv[1], "-"))
		return (ft_cd_back(data));
	else if (chdir(argv[1]) == 0)
		return (ft_update_pwd(data), 1);
	str = ft_strjoin("-minishell: 2 cd: ", argv[1]);
	perror(str);
	free(str);
	return (0);
}
