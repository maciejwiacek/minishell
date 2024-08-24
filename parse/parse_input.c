/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiacek <mwiacek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:31:36 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/20 20:25:49 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_unclosed_quotes(char *input)
{
	char	quote;

	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			quote = *input;
			input++;
			while (*input != quote)
			{
				if (!*input)
					exit_program("Unclosed quotes", EXIT_FAILURE);
				input++;
			}
		}
		input++;
	}
}

static void	check_syntax(char *input)
{
	char	op;

	op = input[ft_strlen(input) - 1];
	if (op == '\'')
		op = input[ft_strlen(input) - 2];
	if (op == '|' || op == '<' || op == '>')
		exit_program("Syntax error", EXIT_FAILURE);
}

void	parse_input(t_shell *shell, char *input)
{
	char	**commands;

	check_unclosed_quotes(input);
	check_syntax(input);
	commands = fill_commands(shell, input);
	parse_commands(shell, commands);
}