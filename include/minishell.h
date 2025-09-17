/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 08:20:34 by pgomes            #+#    #+#             */
/*   Updated: 2025/09/17 09:57:50 by pgomes           ###   ########.fr       */
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
# include <errno.h>



extern int g_status;

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
    int     nb_args;
}						t_token;

typedef struct s_ast
{
    char *value;
    char **args;
    char **argv;
    int nb_args;
    struct s_ast *right;
    struct s_ast *left;
    t_type type;
}               t_ast;

typedef struct s_error
{
    char *msg;
    bool error;
}           t_error;

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
    char **argv_env;
    int exit_status;
    t_list *list_token;
    t_list *list_env;
    t_ast   *ast;
    t_token *token;
    t_env *env;
    t_error *error;
    t_list *tmp;
    
}   t_data;

int ft_exec_heroduc(t_data *data, t_ast *ast);
void ft_sigint_handler(int sig);
int ft_is_empty(char *line);
int ft_load_redir(t_ast *ast, int *new_fd, int *orig_fd);
void ft_setup_signals(void);
t_ast *ft_creat_root(t_data *data);
int ft_check_cmd(char *file);
int ft_execute(t_data *data, t_ast *ast);
void ft_load_ats_argv(t_data *data, t_ast *ast);
void ft_load_env_argv(t_data *data);
int ft_execute_builtins(t_data *data, char **argv);
int ft_is_builtin(char *cmd);
int ft_cd(t_data *data, char *argv[]);
int ft_unset(t_data *data, char *args);
int ft_echo(char *argv[]);
int ft_pwd(void);
int ft_export(t_data *data, char **args);
void ft_exit(t_data *data);
char *ft_expander(t_data *data, char *args);
char *ft_getenv_value(t_list *list, char *key);
void ft_clear_matrix(char **matrix);
int ft_add_env(t_data *data, char *key, char *value);
int ft_setenv_value(t_data *data, char *key, char *value);
void ft_clear_ast(t_ast **root);
char *ft_gettype_redir_value(t_type type);
void ft_parse_error(t_data *data, int i);
void ft_advance_token(t_data *data);
void clear_token_other(void *to);
void clear_env(void *token);
void print_env(void *en);
void print_ast(t_ast *root);
int ft_add_token(t_data *data, char *value,  t_type type);
int ft_check_error(t_data *data, char c);
void ft_extract_env(t_data *data, char **env);
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