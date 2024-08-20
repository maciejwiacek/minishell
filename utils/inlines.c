/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inlines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msmajdor <msmajdor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:15:00 by msmajdor          #+#    #+#             */
/*   Updated: 2024/08/19 15:47:40 by mwiacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

inline bool	is_operator(const char c)
{
	return (c == '|' || c == '<' || c == '>');
}

inline bool	is_space(const char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

inline bool	is_quote(const char c)
{
	return (c == '\'' || c == '\"');
}
