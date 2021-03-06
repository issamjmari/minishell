/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:39:41 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/06/29 16:40:51 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "library/library.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>

# define PIPE '|'
# define SINGLE_QUOTE '\''
# define UNDER_SCORE '_'
# define DOUBLE_QUOTE '\"'
# define EQUAL '='
# define SPACE ' '
# define DOLLAR_SIGN '$'
# define TRUE 1
# define FALSE 0
# define RED_INPUT '<'
# define RED_OUTPUT '>'
# define STD_INPUT 0
# define STD_OUTPUT 1
# define ZERO '0'

typedef struct preparing_vars
{
	char	**splitted_by_space;
	char	**splitted_by_pipe;
	char	**new_env;
	int		commands_number;
	int		ret;
}				t_preparing_vars;
typedef struct dollar_sign_vars
{
	int		index_saver;
	char	*env_value;
	char	*first_part;
	char	*to_be_expanded;
	char	*temp;
	char	*temp1;
}	t_dollar_sign_vars;

typedef struct cmd_path
{
	char		*full_path;
	char		**path;
	char		*temp;
	char		*temp1;
	int			i;
}	t_cmd_path;

typedef struct returned_data
{
	char					*cmd_path;
	char					*cmd_dup;
	char					**args;
	int						input_fd;
	int						output_fd;
	int						str_idx;
	int						is_executable;
	char					**new_env;
	int						exit_stat;
	struct returned_data	*next;
	int						flag;
}	t_returned_data;

typedef struct here_doc_vars
{
	int			p[2];
	char		*s;
	char		*entered_data;
}				t_here_doc_vars;

typedef struct add_space_vars
{
	int		i;
	int		j;
	int		new_string_length;
	char	*new_string;
	int		in_quote;
}			t_add_space_vars;

typedef struct data
{
	char	*context;
	int		value;
	int		index;
}			t_data;

typedef struct expanding_vars
{
	t_data	data;
	int		in_quote;
	int		is_limiter;
	char	*saver;
	char	*temp;
	int		x;
	int		j;
}			t_expanding;
typedef struct remove_quotes_vars
{
	char	*new_string;
	int		i;
	int		j;
	int		new_string_length;
}			t_remove_quotes_vars;

typedef struct error_handling_vars
{
	int	i;
	int	in_quote;
	int	is_first_enter;
}				t_error_handling_vars;

typedef struct g_str
{
	long long	exit_stat;
	int			flag_for_here;
	int			saver;
	int			flag;
	int			cd_flag;
}				t_str;

typedef struct pipe_vars
{
	int		(*pipes_array)[2];
	int		i;
	int		temp_input;
	char	**ptr;
}			t_pipe_vars;

t_str	g_key;
void	skip_spaces(t_error_handling_vars *vars, char *context);
char	*get_next_line(int fd);
void	ft_free(char **s);
void	returned_data_addback(t_returned_data **returned_data, \
	t_returned_data *new);
void	prompt(char **env, t_list *new_env);
int		prompt_helper(char *str);
void	replace_with_real_value(t_returned_data *returned_data, \
char	*real_value, char *saver, int dollar_position);
void	remove_the_word(t_returned_data *data, char *saver, int position);
void	ft_strcpy(char *s, char *str, int start_position, int length);
void	double_quotes(t_data *data, char **env, int is_double_quotes);
void	dollar_sign(t_returned_data *data, char **env, int dollar_position);
char	*search_in_env(char *data, char **env);
void	sig_handler(int l);
void	cd(char **paths, t_list **env);
int		ft_strstr(const char *s1, const char *s2);
void	pwd(void);
void	ft_exit(char **ex);
int		is_int(char *str);
void	ft_echo(char **s);
void	ft_env(t_list **env);
int		built_check(t_returned_data *ret, t_list **env);
void	ft_export(t_list **env, char **args);
void	delete_node(t_list **env, int pos);
void	ft_unset(t_list **env, char	**args);
int		ft_equal(char *arg);
void	searching_for_dollar_sign(t_returned_data **data, char **env);
void	exec(t_returned_data *data, char **env, t_list **env_l);
int		built_exist(char *cmd_path);
void	dup_and_close(t_returned_data *data, int c);
void	close_and_wait(t_returned_data *data, int counter, int *id);
int		lst_count(t_returned_data *data);
void	close_all_pipes(t_returned_data *head);
void	sig_quit(int l);
void	ft_free_list(t_returned_data *head);
void	ft_dupping(t_returned_data *data, int check);
void	all_about_free(char *s1, char *s2, char *s3);
char	**get_new_env(t_list *env);
void	ft_strcpy(char *s, char *str, int start_position, int length);
int		redirection_counter(t_list *splitted_data, char redirection);
char	*search_in_env(char *entered_data, char **env);
void	all_about_free(char *s1, char *s2, char *s3);
char	*join_exit_stat(char *str);
char	**get_new_env(t_list *env);
void	export_error(char **split_arg, char **arg, int *i);
char	*remove_quotes(char *context);
void	in_a_quote(int *in_quote, int SINGLE_OR_DOUBLE);
int		get_length(char **args);
void	execve_err(t_returned_data *data);
t_list	*ft_lstdup(t_list *a);
void	set_oldpwd(t_list **env, char *old);
void	free_dup(t_list *en);
t_list	*ft_lstnew_e(char *content);
#endif
