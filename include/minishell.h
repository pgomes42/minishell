/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:20:34 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/02 12:00:05 by pgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/header/libft.h"

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/wait.h>
# include <termios.h>


typedef enum e_type
 {
    T_COMAND,
    T_PIPE,
    T_IN_REDIR,
    T_OUT_APP_REDIR,
    T_OUT_SUB_REDIR,
    T_HERODUC

 }      t_type;

 typedef struct s_token
{
	t_type		        type;
	char				*value;
    char                **args;
}						t_token;

typedef struct s_ast
{
    char *value;
    char **args;
    struct s_ast *right;
    struct s_ast *left;
    t_type type;
}               t_ast;

typedef struct s_env
{
   char *key;
   char *value;
}               t_env;


typedef struct s_data
{
    int status;
    char *prompt;
    char *line;
    char *error;
    int exit_status;
    t_list *list_token;
    t_list *list_env;
    t_ast   *ast;
    t_token *token;
    t_env *env;
    
}   t_data;

void clear_token_other(void *to);
void clear_env(void *token);
void print_env(void *en);
int ft_add_token(t_data *list_token, char *value,  t_type type);
int ft_check_error(t_data *data, char c);
void ft_extrat_env(t_data *data, char **env);
void ft_tokenizing(t_data *token, char *line);
void print_token(void *token);
void clear_token(void *token);
int is_redir_or_pipe(char c);
int	ft_isspace(char c);
int ft_isseparator(char c);
int ft_isquote(char c);
void ft_skipspace(char **str);
t_type ft_gettype_redir_or_pipe(char *line);
void ft_addargs_token(t_token *token, char *new_args);

#endif