/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 05:37:56 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/21 06:53:42 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_prompt_continue(t_data *data, char *user, char *home,
		char *cwd, char *rel_path)
{
	size_t	prompt_len;
	char	*host;

	host = NULL;
	free(data->prompt);
	prompt_len = ft_strlen(user) + ft_strlen(home) + ft_strlen(rel_path) + 10;
	data->prompt = (char *)malloc(prompt_len);
	if (!data->prompt)
	{
		perror("Error to alocate memory for prompt");
		(free(cwd), free(home));
		return ;
	}
	snprintf(data->prompt, prompt_len, "%s@%s:%s$ ", user, host, rel_path);
}

void	ft_update_prompt(t_data *data)
{
	char	*user;
	char	*home;
	char	*cwd;
	char	*rel_path;

	user = ft_get_envlst_val(data, "USER");
	home = ft_get_envlst_val(data, "NAME");
	cwd = getcwd(NULL, 0);
	rel_path = NULL;
	if (!cwd || !home)
	{
		cwd = ft_strdup("unknown");
		home = ft_strdup("unknown");
	}
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		rel_path = cwd + ft_strlen(home);
		if (*rel_path == '/')
			rel_path++;
	}
	else
		rel_path = cwd;
	ft_update_prompt_continue(data, user, home, cwd, rel_path);
	(free(cwd), free(home));
}
char	*create_prompt(void *data)
{
	size_t	prompt_len;
	char	*prompt;
	char	*user;
	char	*name;
	char	*separator;

	name = ft_get_envlst_val(data, "NAME");
	separator = ":/ ";
	user = ft_get_envlst_val(data, "USER");
	if (!user || !name)
		return (free(user), free(name), NULL);
	prompt_len = ft_strlen(user) + 1 + ft_strlen(name) + ft_strlen(separator)
		+ 1;
	prompt = (char *)malloc(prompt_len);
	if (!prompt)
	{
		perror("Erro ao alocar memória para o prompt");
		return (free(user), free(name), NULL);
	}
	ft_strlcpy(prompt, user, prompt_len);
	ft_strlcat(prompt, "@", prompt_len);
	ft_strlcat(prompt, name, prompt_len);
	ft_strlcat(prompt, separator, prompt_len);
	free(user);
	free(name);
	return (prompt);
}
