/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiacek <mwiacek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:55:34 by mwiacek           #+#    #+#             */
/*   Updated: 2024/08/19 15:33:00 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envp	*search_var(t_envp *envp, char *key)
{
	t_envp	*tmp;

	if (!envp)
		return (NULL);
	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
