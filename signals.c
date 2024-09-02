/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiacek <mwiacek@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:48:53 by mwiacek           #+#    #+#             */
/*   Updated: 2024/09/01 16:01:31 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_prompt(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	exit_heredoc(int signum)
{
	write(1, "\n", 1);
	exit(signum);
}

static void	int_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

static void	quit_handler(int signum)
{
	(void)signum;
	printf("Quit (core dumped)\n");
}

void	signal_handler(bool is_exec)
{
	if (is_exec)
	{
		signal(SIGINT, int_handler);
		signal(SIGQUIT, quit_handler);
	}
	else
	{
		signal(SIGINT, display_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
}