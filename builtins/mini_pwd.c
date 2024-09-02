/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:06:45 by msmajdor          #+#    #+#             */
/*   Updated: 2024/09/01 16:12:27 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_pwd(t_hell hell, t_env *env)
{
	char	*value;

    (void)env;
	if (hell.argv[0])
	{
		ft_putstr_fd("PWD does not take any arguments\n", STDERR_FILENO);
		return (2);
	}
	value = getcwd(NULL, 0);
	ft_putstr_fd(value, 1);
	ft_putstr_fd("\n", 1);
	free(value);
	return (0);
}
