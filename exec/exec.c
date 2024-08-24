/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:07:20 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/25 00:59:55 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_path(char *cmd)
{
	char *env_path;
	char *path;
	char **paths;
	
	env_path = getenv("PATH"); // do zmiany na wlasna funckcje ktora szuka w shell->envp
	paths = ft_split(env_path, ':');
	for (int i = 0; paths[i]; i++) // change to while
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (NULL);
}

int	get_outfile(t_cmd *cmd)
{
	int fd;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->op == GT || tmp->op == GTGT)
	{
		if (tmp->op == GT)
			fd = open(tmp->next->av[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(tmp->next->av[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		tmp = tmp->next;
		if (tmp->op == GT || tmp->op == GTGT)
			close(fd);
		else
			return (fd);
	}
	return (-1);
}

static int	get_infile(t_cmd *cmd)
{
	int		fd;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->op == LT)
	{
		fd = open(tmp->next->av[0], O_RDONLY);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", tmp->next->av[0]);
			return (-1);
		}
		tmp = tmp->next;
		if (tmp->op == LT)
			close(fd);
		else
			return (fd);
	}
	return (-1);
}

static void	handle_right(t_shell *shell, t_cmd *cmd)
{
	int		fd;
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		fd = get_outfile(shell->cmd);
		if (fd != -1)
			dup2(fd, STDOUT_FILENO);
		else
			exit(0);
		if (mini_exec(shell, cmd) == -1)
		{
			path = find_path(cmd->av[0]);
			execve(path, cmd->av, NULL);
		}
		else
			exit(0);
	}
	waitpid(pid, NULL, 0);
	close(fd);
}

static void	handle_left(t_shell *shell, t_cmd *cmd)
{
	int		fd;
	int		fd2;
	pid_t	pid;
	char	*path;
	t_shell *tmp;

	pid = fork();
	tmp = shell;
	if (pid == 0)
	{
		fd = get_infile(shell->cmd);
		if (fd != -1)
			dup2(fd, STDIN_FILENO);
		else
			exit(0);
		while (tmp->cmd->op == LT)
			tmp->cmd = tmp->cmd->next;
		if (tmp->cmd->op == GT || tmp->cmd->op == GTGT)
			fd2 = get_outfile(tmp->cmd);
		if (fd2 != -1)
			dup2(fd2, STDOUT_FILENO);
		else
			exit(0);
		if (mini_exec(shell, cmd) == -1) {
			path = find_path(cmd->av[0]);
			execve(path, cmd->av, NULL);
		}
		else
			exit(0);
	}
	waitpid(pid, NULL, 0);
	close(fd);
}

static void	handle_redir(t_shell *shell)
{
	char	*path;

	if (shell->cmd->op == LT)
	{
		handle_left(shell, shell->cmd);
		while (shell->cmd->op == LT)
			shell->cmd = shell->cmd->next;
		while (shell->cmd->op == GT || shell->cmd->op == GTGT)
			shell->cmd = shell->cmd->next;
	}
	else if (shell->cmd->op == GT || shell->cmd->op == GTGT)
	{
		handle_right(shell, shell->cmd);
		while (shell->cmd->op == GT || shell->cmd->op == GTGT)
			shell->cmd = shell->cmd->next;
	}
	else
	{
		if (mini_exec(shell, cmd) == -1)
		{
			path = find_path(cmd->av[0]);
			execve(path, cmd->av, NULL);
		}
	}
}

void	exec(t_shell *shell)
{
	handle_redir(shell);
}
