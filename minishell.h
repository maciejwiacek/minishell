/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiacek <mwiacek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:17:44 by mwiacek           #+#    #+#             */
/*   Updated: 2024/08/14 15:33:34 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;

typedef enum e_ops
{
	NONE,
	PIPE,
	LT,
	GT,
	LTLT,
	GTGT,
	END,
}	t_ops;

typedef struct s_token
{
	char	*value;
	t_ops	operator;
	t_token	*next;
}	t_token;

typedef struct s_cmd
{
	char	**av;
	char	**envp;
	t_ops	op;
	t_cmd	*next;
}	t_cmd;

// UTILS
bool	is_operator(const char c);
bool	is_space(const char c);
bool	is_quote(const char c);
void	exit_program(const char *message, const int status);
void	*safe_malloc(size_t size);
void	free_lists(t_token **token, t_cmd **cmd);
char	*search_envp(char **envp, char *key);

// PARSING
void	tokenize(t_token **token, char *input);
void	fill_commands(t_cmd **cmd, t_token **token);

// BUILTINS
int		mini_cd(t_cmd *cmd);
int		mini_echo(t_cmd *cmd, char **argv);
int		mini_env(t_cmd *cmd);
int		mini_exec(t_cmd *cmd);
int		mini_pwd(t_cmd *cmd);

#endif
