/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:11:24 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 21:09:14 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_from_child(t_data **data, t_command *temp_cmd, int e_status)
{
	close_pipes(data, (*data)->count_pipes - 1);
	free((*data)->command->cmd_path);
	free((*data)->pipe_end);
	(*data)->command = temp_cmd;
	free_memory(data, 1);
	exit(e_status);
}

void	ft_first_cmd(t_data **data, t_command **command, int fd,
	t_command *temp_cmd)
{
	if (get_pid(*command) == 0)
	{
		(*command)->cmd_path = find_fullpath(data,
				(*command), &(*command)->cmd_path);
		fd = open_fd(*command);
		if (fd == 1)
		{
			if ((*command)->output.type == PIPE)
			{
				dup2((*data)->pipe_end[2 * 0 + 1], STDOUT_FILENO);
				close_pipes(data, (*data)->count_pipes - 1);
			}
			run_cmd(data, *command, &(*command)->cmd_path, temp_cmd);
		}
		if (fd == 0 || fd == -1)
			exit_from_child(data, temp_cmd, EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	(*command) = (*command)->next;
}

void	ft_middle_cmd(t_data **data, t_command **command, int fd,
	t_command *temp_cmd)
{
	int	i;

	i = 0;
	while (++i < ((*data)->count_pipes))
	{
		if (get_pid(*command) == 0)
		{
			(*command)->cmd_path = find_fullpath(data,
					(*command), &(*command)->cmd_path);
			fd = open_fd(*command);
			if (fd == 1)
			{
				if ((*command)->input.type == PIPE)
					dup2((*data)->pipe_end[2 * i - 2], STDIN_FILENO);
				if ((*command)->output.type == PIPE)
					dup2((*data)->pipe_end[2 * i + 1], STDOUT_FILENO);
				close_pipes(data, (*data)->count_pipes - 1);
				run_cmd(data, *command, &(*command)->cmd_path, temp_cmd);
			}
			if (fd == 0 || fd == -1)
				exit_from_child(data, temp_cmd, EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		(*command) = (*command)->next;
	}
}

// ft_printf("arg %s %s %s\n", (*command)->arguments[0],
// (*command)->arguments[1],(*command)->arguments[2]);
void	ft_last_cmd(t_data **data, t_command **command, int fd,
	t_command *temp_cmd)
{
	if (get_pid(*command) == 0)
	{
		(*command)->cmd_path = find_fullpath(data,
				(*command), &(*command)->cmd_path);
		fd = open_fd(*command);
		if (fd == 1)
		{
			if ((*command)->input.type == PIPE 
				|| (*command)->input.type == NONE)
			{
				dup2((*data)->pipe_end[2 * ((*data)->count_pipes) - 2],
					STDIN_FILENO);
				close_pipes(data, (*data)->count_pipes - 1);
			}
			run_cmd(data, *command, &(*command)->cmd_path, temp_cmd);
		}
		if (fd == 0 || fd == -1)
			exit_from_child(data, temp_cmd, EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
}

void	execute_multiple_cmd(t_data **data)
{
	t_command	*temp;
	int			fd;

	fd = 0;
	temp = (*data)->command;
	(*data)->pipe_end = NULL;
	(*data)->pipe_end = (int *)malloc(
			((*data)->count_pipes * 2) * sizeof(int));
	if (!(*data)->pipe_end)
		return ;
	ft_create_pipe(data);
	ft_first_cmd(data, &(*data)->command, fd, temp);
	if ((*data)->count_pipes > 1)
		ft_middle_cmd(data, &(*data)->command, fd, temp);
	ft_last_cmd(data, &(*data)->command, fd, temp);
	close_pipes(data, (*data)->count_pipes - 1);
	wait_child_process(data, 0);
	free((*data)->pipe_end);
	(*data)->command = temp;
}
