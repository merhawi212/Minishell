/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:55:33 by Degef             #+#    #+#             */
/*   Updated: 2023/08/05 07:55:33 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define EXIT_HERE_DOC 300

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>

int	g_exit_status;

// Token types enumeration
typedef enum s_tokentype
{
	NONE = -1,
	B_COMMAND,
	PIPE,
	GREAT,
	LESS,
	GREAT_GREAT,
	LESS_LESS,
	UNKNOWN,
	DELIMITER,
}	t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type	type;
	int				t_len;
	char			*value;
}	t_token;

typedef struct s_redirection
{
	char			*name;
	char			*filename;
	t_token_type	type;
	bool			is_delimiter_in_quote;
}	t_redirection;

typedef struct s_command
{
	char				*name;
	char				**arguments;
	char				*cmd_path;
	bool				is_runable;
	bool				has_file_err;
	t_redirection		input;
	t_redirection		output;
	struct s_command	*next;
	struct s_command	*previous;
}	t_command;

typedef struct s_data
{
	char		*input;
	char		*mod_input;
	t_token		*tokens;
	char		*path;
	int			stop_heredoc;
	int			count_pipes;
	int			*pipe_end;
	int			*p_end;
	int			export_fds[2];
	char		**splitted_path;
	char		**env;
	char		**env_sorted;
	int			input_fd;
	int			exit_status;
	t_command	*command;
}	t_data;

//Lex
int				lex(t_data **data);
void			get_token_type(t_token *token, char **t_splitted, int t_count);
int				len_if_quote(char *str, int i, char c);
int				check_syntax_error(t_data **data, t_token *tokens, int i);
void			perror_free(t_data **data, char *str, char *value,
					int free_only);

//tokenize
void			check_if_capital(t_token *token,
					char **t_splitted, int t_count);

//check file presence 
int				check_dir_existance(t_data **data, t_token *tokens,
					int i, char *str);
char			*remove_quote_and_cwd_indicator(t_data **data, int i);
char			*trim_dir_from_back(char *value);

void			get_token_type(t_token *token,
					char **t_splitted, int t_count);
void			build_tokens(t_data **data);

//separate charachters
int				separate_characters(t_data **data, char	**input);
void			separate_characters_utils(char *input, int *i,
					int *j, char **result);

void			remove_unnecessary_quote(t_data **data);

//remove extra space
void			remove_extra_spaces(char	**input, t_data **data);

//split input
char			**split_input(char *str, char c);

/* ----------- start of PARSER -----------------*/
//parser and parsing utils
int				get_double_pointer_len(char **arr);
int				parser(t_data **data);
t_command		*lstlast(t_command *lst);
bool			handle_unclosed_quotes(t_data **data);
int				all_space(char *input, t_data **data);
void			print_error2(char *s1, char *s2, char *s3);
void			mark_commands(t_data **data);
void			update_hasfile_err(t_command **cmd);

// full_path_handler.c
int				find_command(t_data **data, char *str);
int				find_command_without_perror(t_data **data, char *str);
int				is_cmd_executable_without_perror(char *str);

/* ----------- end of PARSER -----------------*/

//expander
int				expand(t_data **data);
char			*check_expansion(char *arg, t_data **data);
char			*search_value(char *var_name, t_data **data);
int				replace_tilde_with_home(t_data **data);

//redirections
void			identify_redirections(t_data **data, int *i);

//check command and check command utils
int				is_non_b_command(char *str, t_data **data, int count_pipes);
char			*get_full_path(char *dir, char *command,
					char *fullPath);
int				command_present(t_data **data, int i, int token_len);
// excution 
void			handle_exc(t_data **data);
void			exe_b_cmd(char *command_name,
					char **command_arguments, t_data **data, t_command *temp);
void			run_cmd(t_data **data, t_command *command, char **full_path,
					t_command *temp_cmd);

// builtin
void			ft_echo(char **arguments, t_data **data);
void			ft_pwd(void);
void			ft_cd(char **arguments, t_data **data);
void			ft_exit(t_data **data, char **args);
void			ft_env(char **arg, t_data **data);

//export && export utils
void			ft_export(t_data **data, char **arguments);
int				len_char(char *str, char c);
void			sort_envp(t_data **data, char c);
void			put_envp(char **env, t_data **data, int i);
char			**copy_env(char **envp, int add);

//unset
void			ft_unset(char **args, t_data **data);

//free
void			free_double_array(char ***str);
void			free_tokens(t_data **data);
void			free_command(t_command *command);
void			free_memory(t_data **data, int free_env);

// exec_utils
void			ft_create_pipe(t_data **data);
int				get_pid(t_command *cmd);
int				is_builtin(char *command_name);
void			close_pipes(t_data **data, int i);
char			*find_fullpath(t_data **data, t_command *command,
					char **full_path);
int				wait_child_process(t_data **data, int status);

//exec_multiple_cmds
void			execute_multiple_cmd(t_data **data);
void			exit_from_child(t_data **data, t_command *temp_cmd,
					int e_status);

//exec_sngle_cmd
void			exec_one_cmd(t_data **data, t_command *command);

// fd_handler.c
int				get_fd(t_command *command, int token_type);
int				open_fd(t_command *command);
void			print_error(char *s1, char *s2, char *s3);

//here doc
int				get_here_doc(t_command *cmd, t_data **data);
int				check_here_doc(t_data **data);

//signal handler
void			handle_signals(void);
void			rl_replace_line(const char *text, int clear_undo);
void			child_signal_handler(int num);
void			signal_controller(int sig_num);
void			here_doc_signal(int sig_num);
void			child_signals(t_command *cmd);
void			sigint_here_doc_handler(int sig);
void			sigint_child_here_doc_handler(int sig);

#endif
