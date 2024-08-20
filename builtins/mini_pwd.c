/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiacek <mwiacek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:45:15 by mwiacek           #+#    #+#             */
/*   Updated: 2024/08/14 15:23:24 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = search_envp(cmd->envp, "PWD");
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}