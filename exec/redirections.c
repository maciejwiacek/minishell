/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:57:53 by msmajdor          #+#    #+#             */
/*   Updated: 2024/09/01 16:25:55 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc(t_hell *hell, int i)
{
	int		fd;
	char	*input;
	char	*tmp_file;

	tmp_file = ".heredoc_tmp";
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, exit_heredoc);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("EOF received\n");
			break ;
		}
		if (ft_strncmp(input, hell->argv[i + 1], sizeof(input)) == 0)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
	close(fd);
	fd = open(tmp_file, O_RDONLY, 0644);
	dup2(fd, 0);
	free(hell->argv[i]);
	free(hell->argv[i + 1]);
	hell->argv[i] = NULL;
	close(fd);
	unlink(tmp_file);
}

static void	redirect_input(t_hell *hell, int i)
{
	int		fd;

	fd = open(hell->argv[i + 1], O_RDONLY, 0644);
	if (fd == -1)
		return (ft_putstr_fd("Filed to handle a file\n", 2));
	dup2(fd, 0);
	free(hell->argv[i]);
	free(hell->argv[i + 1]);
	hell->argv[i] = NULL;
	close(fd);
}

static void	redirect_output(t_hell *hell, int i)
{
	int		fd;

	if (ft_strncmp(hell->argv[i], ">>", 2) == 0)
		fd = open(hell->argv[i + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(hell->argv[i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_putstr_fd("Filed to handle a file\n", 2));
	dup2(fd, 1);
		// ill check if needed for proper working, maciej will look for leaks
	free(hell->argv[i]);
	free(hell->argv[i + 1]);
	hell->argv[i] = NULL;
	close(fd);
}

void	redirect(t_hell *hell)
{
	int	i;

	i = 0;
	while (hell->argv[i])
	{
		if (ft_strncmp(hell->argv[i], ">", 1) == 0)
			redirect_output(hell, i);
		else if (ft_strncmp(hell->argv[i], "<<", 2) == 0)
			heredoc(hell, i);
		else if (ft_strncmp(hell->argv[i], "<", 1) == 0)
			redirect_input(hell, i);
		i++;
	}
}
