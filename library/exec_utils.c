/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijmari <ijmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:01:46 by ijmari            #+#    #+#             */
/*   Updated: 2022/06/24 16:11:35 by ijmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_and_close(t_returned_data *data, int c)
{
	if (c == 'i')
	{
		dup2(data->input_fd, STD_INPUT);
		close (data->input_fd);
	}
	else
	{
		dup2(data->output_fd, STD_OUTPUT);
		close (data->output_fd);
	}
}

void	close_and_wait(t_returned_data *data, int counter, int *id)
{
	int	i;
	int	status;

	close_all_pipes(data);
	i = 0;
	while (i < counter)
	{
		waitpid(id[i], &status, 0);
		if (WIFEXITED(status))
			g_key.exit_stat = WEXITSTATUS(status);
		if (status == 2)
			g_key.exit_stat = 130;
		if (status == 3)
			g_key.exit_stat = 131;
		i++;
	}
}

int	lst_count(t_returned_data *data)
{
	int	len;

	len = 0;
	while (data)
	{
		len++;
		data = data->next;
	}
	return (len);
}

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	ft_dupping(t_returned_data *data, int check)
{
	if (data->input_fd != 0 && !check)
		dup_and_close(data, 'i');
	if (check)
		if (data->input_fd)
			close (data->input_fd);
	if (data->output_fd != 1)
		dup_and_close(data, 'o');
}
