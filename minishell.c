/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:01:37 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/19 15:36:50 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (shell.exit == false)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		parse_input(&shell, ft_strtrim(input, " \t\n\r\v\f"));
		mini_exec(&shell, shell.cmd);
		add_history(input);
		free(input);
	}
	return (0);
}

//		///////////////////////////////////////////////////
//		t_cmd *tempcmd = shell.cmd;
//		while (tempcmd) {
//			for (size_t i = 0; tempcmd->av[i]; i++)
//				printf("av: %s ", tempcmd->av[i]);
//			printf("op: %d\n", tempcmd->op);
//			tempcmd = tempcmd->next;
//			printf("next\n");
//		}
//		///////////////////////////////////////////////////