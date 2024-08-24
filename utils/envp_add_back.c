/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiacek <mwiacek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:41:21 by mwiacek           #+#    #+#             */
/*   Updated: 2024/08/19 15:41:40 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envp_add_back(t_envp **envp, char *key, char *value)
{
	t_envp	*new_item;
	t_envp	*cur;

	new_item = safe_malloc(sizeof(t_envp));
	new_item->key = ft_strdup(key);
	new_item->value = ft_strdup(value);
	new_item->next = NULL;
	if (*envp == NULL)
	{
		*envp = new_item;
		return ;
	}
	cur = *envp;
	while (cur->next)
		cur = cur->next;
	cur->next = new_item;
}