/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:03:24 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/22 15:57:11 by msmajdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum e_ops
{
	PIPE,
	LT,
	GT,
	LTLT,
	GTGT,
	END,
}	t_ops;

typedef struct s_envp	t_envp;
typedef struct s_cmd	t_cmd;

typedef struct s_envp
{
	char	*key;
	char	*value;
	t_envp	*next;
}	t_envp;

typedef struct s_cmd
{
	char	**av;
	t_ops	op;
	t_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_cmd	*cmd;
	t_envp	*envp;
	bool	exit;
}	t_shell;

void	init_shell(t_shell *shell, char **envp);

// PARSE
void	parse_input(t_shell *shell, char *input);
char	**fill_commands(t_shell *shell, char *input);
size_t	get_commands_len(char *input);
size_t	get_command_len(t_shell *shell, char *input);
size_t	get_env_len(t_shell *shell, char **input);
void	parse_commands(t_shell *shell, char **commands);

// UTILS
void	exit_program(const char *message, const int status);
bool	is_space(const char c);
bool	is_quote(const char c);
void	skip_spaces(char **input);
void	*safe_malloc(size_t size);
t_envp	*search_var(t_envp *envp, char *key);
void	envp_add_back(t_envp **envp, char *key, char *value);

// BUILTINS
int		mini_exec(t_shell *shell, t_cmd *cmd);
int		mini_cd(t_shell *shell, t_cmd *cmd);
int		mini_echo(char **argv);
int		mini_env(t_envp *envp);
int		mini_pwd(void);
int		mini_unset(t_envp *envp, t_cmd *cmd);
int		mini_export(t_envp *envp, t_cmd *cmd);

void	exec(t_shell *shell);

#endif
