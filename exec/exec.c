/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:07:20 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/23 12:14:59 by msmajdor         ###   ########.fr       */
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

void	redirect(t_cmd **cmd, char **root_cmd) {
	// troche zle
	// todo: otworzyc wszyskie pliki przed execve

	pid_t	pid;
	char	*path;
	int		fd;

	pid = fork();
	*cmd = (*cmd)->next;
	printf("%s\n", (*cmd)->av[0]);
	if (pid == -1)
	{
		printf("fork error\n");
		return ;
	}
	if (pid == 0)
	{
		fd = open((*cmd)->av[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		path = find_path(root_cmd[0]);
		dup2(fd, 1);
		execve(path, root_cmd, NULL);
		close(fd);
	}
	waitpid(pid, NULL, 0);
	if ((*cmd)->op == GT)
		redirect(cmd, root_cmd);
}

void	exe_cmd(t_cmd *cmd)
{
	char **root_cmd;

	while (cmd)
	{
		root_cmd = cmd->av;
		if (cmd->op == GT)
			redirect(&cmd, root_cmd);
		if (cmd->op == END)
			break ;
	}
}

// loop through the cmd and if < is seen create a file and redirect the output to it
void	exec(t_shell *shell)
{
	pid_t	pid;
	char	*path;

	if (mini_exec(shell, shell->cmd) == 0)
		return ;
	exe_cmd(shell->cmd);
	// printf("exec\n");
	// pid = fork();
	// if (pid == -1) /// safe fork todo
	// {
	// 	printf("fork error\n");
	// 	return ;
	// }
	// if (pid == 0)
	// {
	// 	path = find_path(shell->cmd->av[0]);
	// 	while (shell->cmd->op == GT)
		// {
		// 	shell->cmd = shell->cmd->next;
		// 	int fd = open(shell->cmd->av[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// 	dup2(fd, 1);
		// 	execve(path, shell->cmd->av + 1, NULL);
		// 	close(fd);
		// }
	// 	execve(path, shell->cmd->av, NULL);
	// }
	// printf("exec\n");
	return ;
}
