/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:44:28 by pgomes            #+#    #+#             */
/*   Updated: 2024/11/22 13:16:33 by pgomes           ###   ########.fr       */
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

# define PROMPT "minishell$ "

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

			

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}						t_parse_err_type;

		

typedef struct s_parse_err
{
	t_parse_err_type	type;
	char				*str;
}						t_parse_err;
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}						t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}						t_err_no;


typedef struct s_err
{
	t_err_no			no;
	t_err_msg			msg;
	char				*cause;
}						t_err;

typedef struct s_path
{
	t_err				err;
	char				*path;
}						t_path;

typedef struct s_data
{
	char				*line;
	t_token				*tokens;
	t_token				*curr_token;
	int					exit_s;
	bool				signint_child;
	bool				sigint_received;
	char				**expanded_args;
	t_parse_err			parse_err;
	int					stdin;
	int					stdout;
	int					here_doc;
	char				**environ;
	t_env				*envlst;
	bool				heredoc_sigint;
	char				*prompt;
	struct termios		original_term;
}						t_data;

extern int				g_signal_status;

int						ft_cd(t_data *data);

int						ft_echo(t_data *data);

char					*ft_get_envlst_val(t_data *data, char *key);
bool					ft_env_entry_exists(t_data *data, char *key);
void					ft_update_envlst(t_data *data, char *key, char *value,
							bool create);

char					*ft_extract_key(char *str);
char					*ft_extract_value(char *str);
void					ft_init_envlst(t_data *data);
int						ft_env(t_data *data);

void					ft_exit(t_data *data, char **args);

int						ft_check_key(char *str);
int						ft_export(t_data *data);

int						ft_pwd(void);

int						ft_unset(t_data *data);

void					ft_clean_ms(t_data *data);

int						ft_err_msg(t_err err);

int						ft_exec_builtin(t_data *data, t_token *token);
bool					ft_is_builtin(char *arg);

int						ft_out(t_token *current_token, int *status);
int						ft_in(t_token *current_token, int *status);
int						ft_append(t_token *current_token, int *status);

void					*ft_garbage_collector(void *ptr, bool clean);
bool					ft_is_delimiter(char *delimiter, char *str);

int						ft_get_exit_status(int status);
int						ft_exec_cmd(t_data *data, t_token *current_token,
							bool piped);

t_err					ft_check_exec(char *file, bool cmd);
t_err					ft_check_read(char *file);
t_err					ft_check_write(char *file);

int						ft_check_redirection(t_data *current_data);
void					ft_reset_stds(t_data *data, bool piped);
int						ft_exec_simple_cmd(t_data *data, t_token *token,
							bool piped);

t_path					ft_get_path(t_data *data, char *cmd);

bool					ft_match_star(char *pattern, char *str);

char					*ft_clean_empty_strs(char *str);

bool					ft_is_valid_var_char(char c);
char					*ft_handle_normal_str(char *str, size_t *i);
char					*ft_handle_squotes(char *str, size_t *i);
char					*ft_handle_dquotes(t_data *data, char *str, size_t *i);

char					*ft_handle_dollar(t_data *data, char *str, size_t *i);
char					**ft_expand(t_data *data, char *str);

char					**ft_expander_split(char const *s);

bool					ft_contains_asterisk(char *str);
size_t					ft_str_arr_len(char **str_arr);
size_t					ft_match_count(char *pattern);
char					**ft_join_str_arrs(char ***str_arrs);

char					**ft_globber(char **expanded);

char					*ft_strip_quotes(char *str);

void					ft_heredoc_expander(t_data *data, char *str, int fd);

void					handle_sigquit(int sig);
void					ft_init_signals(t_data *data);

void					ft_set_parse_err(t_data *data, t_parse_err_type type);
void					ft_handle_parse_err(t_data *data);
		
void					ft_get_next_token(t_data *data);
bool					ft_curr_token_is_binop(t_data *data);
bool					ft_is_redir(t_token_type type);
int						ft_prec(t_token_type type);
int						ft_curr_token_prec(t_data *data);

int						ft_append_separator(t_token_type type, char **line_ptr,
							t_token **token_list);
int						ft_append_identifier(t_data *data, char **line_ptr,
							t_token **token_list);

int						ft_handle_separator(char **line_ptr,
							t_token **token_list);
t_token					*ft_tokenization_handler(t_data *data, char *line);

t_token					*ft_new_token(char *value, t_token_type type);
void					ft_token_list_add_back(t_token **lst,
							t_token *new_token);
void					ft_clear_token_list(t_token **lst);

int						ft_is_quote(char c);
int						ft_is_separator(char *s);
void					ft_skip_spaces(char **line);
bool					ft_skip_quotes(char *line, size_t *i);
void					ft_print_quote_err(t_data *data, char c);

t_token					*ft_tokenize(t_data *data);

void					ft_update_prompt(t_data *data);

char					*ft_del_aspas(char *str);
void					ft_init_heroduc(t_data *data);
char					**ft_expand_args(t_data *data, t_token *current_token);
void					ft_init_signals_(void);
void					signals_init(t_data *data);
void					handle_sigint_heredoc(int sig);
void					ft_free_char2(char **tofree);
void					ft_free_char3(char ***tofree);
int						ft_isspace(char c);
#endif
