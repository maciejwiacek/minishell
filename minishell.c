/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:25:37 by msmajdor          #+#    #+#             */
/*   Updated: 2024/09/01 16:01:31 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envp(t_env *env, char **envp)
{
	int	i;

	i = -1;
	while (++i, envp[i])
		;
	env->envp = safe_malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (++i, envp[i])
		env->envp[i] = ft_strdup(envp[i]);
	env->envp[i] = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_hell	*hell;
	t_env	env;

	((void)argc, (void)argv);
	init_envp(&env, envp);
	while (true)
	{
		signal_handler(false);
		input = readline("hell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		hell = parse_input(&env, &input);
		if (!hell)
		{
			free(input);
			continue ;
		}
		execute(&env, hell);
		free_hell(hell);
		free(input);
	}
	free_arr(env.envp);
	return (0);
}
