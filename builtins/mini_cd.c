/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:31:04 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/29 14:37:32 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_status(t_hell *hell)
{
    if (!hell->argv[0])
    {
        ft_putstr_fd("cd: No relative or absolute path specified\n", 2);
        return (1);
    }
    if (chdir(hell->argv[0]) != 0)
    {
        ft_putstr_fd("cd: No such file or directory\n", 2);
        return (1);
    }
	return (0);
}

static void set_env(t_env *env, char *oldpwd)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    del_env(env, "OLDPWD");
    del_env(env, "PWD");
    add_env(env, "OLDPWD", oldpwd);
    add_env(env, "PWD", pwd);
    free(pwd);
}

int	mini_cd(t_env *env, t_hell hell)
{
	int		status;
    char    *oldpwd;

    oldpwd = getcwd(NULL, 0);
    status = get_status(&hell);
    if (status == 0)
        set_env(env, oldpwd);
    free(oldpwd);
	return (status);
}
