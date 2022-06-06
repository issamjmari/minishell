#include "../minishell.h"

void	close_all_pipes(t_returned_data *head)
{
	while (head)
	{
		if (head->input_fd != STD_INPUT)
			close(head->input_fd);
		if (head->output_fd != STD_OUTPUT)
			close(head->output_fd);
		head = head->next;
	}
}
void	close_unused_pipes(t_returned_data *head, t_returned_data *curr, char **env)
{
	int	i;

	i = 0;
	static int j;
	while (head)
	{
		if (head != curr)
		{
			if (head->input_fd != STD_INPUT)
				close(head->input_fd);
			if (head->output_fd != STD_OUTPUT)
				close(head->output_fd);
		}
		head = head->next;
	}
	j++;
}

void 	fill_list(t_returned_data *data, char **env, t_list **env_l)
{
	int	*id;
	int	counter;
	char *path;
	t_returned_data *t = data;
	t_returned_data *temp = data;
	int	len;
	counter = 0;
	while (temp)
	{
		int k = 0;
		printf("cmd is %s\n", temp->cmd_path);
		while (temp->args[k])
			printf("args is %s\n", temp->args[k++]);
		counter++;
		temp = temp->next;
	}
	len = counter;
	id = malloc(counter * sizeof(int));
	counter = 0;
	while (data)
	{
		// printf("cmd is %s\n", data->cmd_path);
		if (built_check(data, env_l))
		{
			printf("is built\n");
		}
		else
		{
			id[counter] = fork();
		if (id[counter] == 0)
		{	
			close_unused_pipes(t, data, env);
			if (data->is_executable)
			{
					if (data->input_fd != 0)
					{
						dup2(data->input_fd, STD_INPUT);
						close (data->input_fd);
					}
					if (data->output_fd != 1)
					{
						dup2(data->output_fd, STD_OUTPUT);
						close (data->output_fd);
					}
					path = get_command_path(env, data->cmd_path);
					if (execve(path, data->args, env) == -1)
						dprintf(2, "HEY \n");
			}	
		}
			}
		data = data->next;
		counter++;
	}
	close_all_pipes(t);
	counter = 0;
	while(counter < len)
		waitpid(id[counter++], NULL, 0);
}