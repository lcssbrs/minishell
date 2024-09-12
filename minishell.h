/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:34:29 by gdornic           #+#    #+#             */
/*   Updated: 2023/12/17 08:46:48 by lseiberr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <libft.h>
# define ERROR_PREFIX "minishell: "
# define PROMPT "minishell> "
# define HERE_DOC_PROMPT "> "

typedef struct s_stream
{
	int	input;
	int	output;
	int	next_input;
	int	previous_output;
	int	saved_stdin_fd;
	int	saved_stdout_fd;
}	t_stream;

//array free
void				array_free(void *root, unsigned int dimension);

//delete node
void				delete_node(t_list **list, t_list *node);

//str merge
char				*str_merge(char *s1, char *s2);

//tokenizer
t_list				*tokenizer(char *input);

//print error
void				print_error(char *prefix, char *error, char *suffix);

//definitions
int					is_space(int c);
int					is_metacharacter(int c);
int					is_operator(char *str);
int					is_redirection_operator(char *str);
int					is_control_operator(char *str);
int					is_pipe(char *str);
int					is_list_operator(char *str);
int					is_left_bracket(char *str);
int					is_right_bracket(char *str);
int					is_word(char *str);
int					is_bracket(char *str);
int					is_or(char *str);
int					is_and(char *str);
int					is_executable(char *path_name);
int					is_builtin(char *cmd);

//function variables
const char			**operators_set(void);
t_stream			*m_stream(void);
int					*m_exit_code(void);
int					*m_last_exit_code(void);
struct sigaction	*m_sa(void);

//token print
void				token_print(t_list *token);

//parser
int					parser(t_list *token, char ***envp_ptr);

//syntax_rules
int					syntax_error(char *content);
int					bracket_count_rule(char *content, char *next_content);
int					syntax_rules(t_list *token);

//execution
int					execution(t_list *token, char ***envp_ptr, int exit_status);

//pipeline execution
int					pipeline_execution(t_list *pipeline, \
char ***envp_ptr, int exit_status);

//command execution
t_list				*next_redirection_operator(t_list *command);
int					command_execution(t_list *command, \
char ***envp_ptr, int exit_status, int builtin_create_subshell);

//builtin execution
int					builtin_execution(char **cmd, \
char ***envp_ptr, int builtin_create_subshell);

//program execution
int					program_execution(char **cmd, char **envp);

//stream
int					m_stream_use(void);
int					m_stream_redirect(t_list *command);
int					pipe_set(int last);
void				m_stream_set(void);

//redirection
int					input_redirect(char *file_name);
int					here_doc(char *delimiter);
int					output_redirect(char *file_name);
int					output_redirect_append(char *file_name);

//expansion
char				*expansion_mark(char *parameter);
t_list				*redirection_expansion(t_list *pipeline, char **envp);
t_list				*classic_expansion(char *word, char **envp);

//parameter expansion
char				*parameter_expansion(char *word, char **envp);

//word split
t_list				*word_split(char *word);

//filename expansion
t_list				*filename_expansion(t_list *token);

//wildcard expansion
char				*next_wildcard(char *word);
t_list				*wildcard_expansion(char *word, t_list *cwd_file);

//quote remove
char				*quote_remove(char *word);
t_list				*quote_removal(t_list *token);

//lstnew secure
t_list				*lstnew_secure(char *content);

//utils.c
int					ft_strcmp(char *s1, char *s2);
int					ft_chr(char *str, char c);
char				*ft_getcwd(char *env, char *pwd, char *choose);
char				**changeenvdir(char **env, int i, char *pwd);
void				ft_else(char **arg, char ***env, int i, char *pwd);

//pwd_builtin.c
int					pwd_builtin(char **arg, char ***env);

//echo_builtin.c
int					echo_builtin(char **arg, char ***env);

//cd_builtin.c
int					cd_builtin(char **arg, char ***env);
int					ft_findoldpwd(char **env);
int					ft_findpwd(char **env);

//env_builtin.c
int					env_builtin(char **arg, char ***env);

//exit_builtin.c
int					exit_builtin(char **arg, char ***env);

//export_builtin.c
int					export_builtin(char **arg, char ***env);
int					changeenv(char ***env, char **arg, int *index);
char				**strplusenv(char *arg, char **env);
int					changeexport(char ***env, char **tab);
char				**cpytab(char **sort);

//utils_export
int					lentillequall(char *str);
int					ft_lentab(char **tab);
void				freetab(char **tab);
int					check_syntax(char *arg);
int					checkarg(char **env, char *arg);

//unset
int					unset_builtin(char **arg, char ***env);
char				**ft_realloc(char **env, int change);

//reverse_split
char				*ft_reverse_split(char **tab);

//sort_env
char				**sort_env(char **env);

//freetab int
int					freetab_int(char **tab);

//signal
void				ft_signalnewline(int sig);
void				ft_signalquit(int sig);
void				signal_do_nothing(int sig);
void				signal_here_doc(int sig);

//path split
char				**path_split(char **envp);

//next list operator
t_list				*next_list_operator(t_list *token);

//quote rule
int					quotes_rule(char *str);

//next mark
char				*next_mark(char *word);

//next pipe
t_list				*next_pipe(t_list *pipeline);

#endif
