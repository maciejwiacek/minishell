/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:15:00 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/14 17:47:24 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	t_token	*token;
	char	*input;

	(void)ac;
	(void)av;
	cmd->envp = envp;
	while (true)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		tokenize(&token, ft_strtrim(input, " \t\n\r\v\f"));
		fill_commands(&cmd, &token);
		add_history(input);
		mini_exec(cmd);
		free(input);
//		free_lists(&token, &cmd);
	}
	return (0);
}
