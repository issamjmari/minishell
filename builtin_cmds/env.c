/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:48:59 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/22 18:05:21 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_list **env)
{
	t_list	*current;

	current = *env;
	change_path_value(env);
	while (current != 0)
	{
		if (current->criteria == 'e')
			printf("%s\n", current->content);
		current = current->next;
	}
}
