/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:47:10 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/29 16:41:19 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	changing(t_list **env, char *arg)
{
	int		len;
	int		j;

	len = ft_strlen(arg);
	if ((*env)->content)
		free((*env)->content);
	(*env)->content = malloc(len + 1);
	j = 0;
	while (arg[j])
	{
		(*env)->content[j] = arg[j];
		j++;
	}
	(*env)->content[j] = '\0';
	(*env)->criteria = 'e';
}

void	change_value(char *arg, t_list **env)
{
	t_list	*curr;
	char	**spl;
	char	**split_arg;

	curr = *env;
	while (*env)
	{
		spl = split_with_equ((*env)->content);
		split_arg = split_with_equ(arg);
		if (ft_equal(arg))
			if (!ft_strcmp(spl[0], split_arg[0]))
				changing(env, arg);
		free_splits(spl, split_arg);
		(*env) = (*env)->next;
	}
	*env = curr;
}

void	add_value(char *arg, t_list **env)
{
	t_list	*curr;
	char	**spl;
	char	**split_arg;

	curr = *env;
	while (*env)
	{
		spl = split_with_equ((*env)->content);
		split_arg = split_with_plus(arg);
		if (split_arg[1])
			if (!ft_strcmp(spl[0], split_arg[0]))
				adding(spl, split_arg, env);
		free_splits(spl, split_arg);
		(*env) = (*env)->next;
	}
	*env = curr;
}

int	ft_isnode(t_list **env, char *arg)
{
	t_list	*curr;
	char	**spl;
	char	**split_arg;
	int		check;

	curr = *env;
	check = there_is_plus(arg);
	while (curr)
	{
		spl = split_with_equ(curr->content);
		if (check)
			split_arg = split_with_plus(arg);
		else
			split_arg = split_with_equ(arg);
		if (!ft_strcmp(spl[0], split_arg[0]))
		{
			ft_free(spl);
			ft_free(split_arg);
			return (1);
		}
		curr = curr->next;
		free_splits(spl, split_arg);
	}
	return (0);
}

void	ft_export(t_list **env, char **args)
{
	int		i;
	char	**split_arg;

	i = 0;
	split_arg = NULL;
	g_key.exit_stat = 0;
	change_path_value(env);
	if (*args == NULL)
		sort_list(*env);
	while (args[i])
	{
		if (args[i][0] != '=')
			split_arg = split_with_equ(args[i]);
		if (!check_if_valid(args[i]) || args[i][0] == '=')
		{
			export_error(split_arg, args, &i);
			continue ;
		}
		else if (ft_isnode(env, args[i]))
			get_things_changed(args, env, i);
		else
			add_it_back(split_arg, args, env, i);
		ft_free(split_arg);
		i++;
	}
}
