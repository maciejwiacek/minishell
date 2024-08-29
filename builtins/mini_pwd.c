/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:06:45 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/29 14:11:34 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_pwd(t_env *env)
{
	char	*value;

    (void)env;
	value = getcwd(NULL, 0);
	ft_putstr_fd(value, 1);
	ft_putstr_fd("\n", 1);
	free(value);
	return (0);
}
