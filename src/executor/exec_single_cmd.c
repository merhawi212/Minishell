/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:10:34 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 20:29:27 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	return_fd(t_command *cmd, int out_fd, int in_fd)
{
	if (cmd->input.type == LESS || cmd->input.type == LESS_LESS)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->output.type == GREAT || cmd->output.type == GREAT_GREAT)
		dup2(out_fd, STDOUT_FILENO);
}

int	run_in_parent(t_data **data, t_command *cmd)
{
	int	out_fd;
	int	in_fd;

	out_fd = 0;
	in_fd = 0;
	if ((cmd->name && is_builtin(cmd->name)))
	{
		if (cmd->name && ft_strcmp(cmd->name, "exit"))
		{
			if (cmd->input.type == LESS || cmd->input.type == LESS_LESS)
				in_fd = dup(STDIN_FILENO);
			if (cmd->input.type == GREAT || cmd->input.type == GREAT_GREAT)
				out_fd = dup(STDOUT_FILENO);
		}
		if (open_fd(cmd) == 1)
			exe_b_cmd(cmd->name, cmd->arguments, data, cmd);
		return_fd(cmd, out_fd, in_fd);
		return (1);
	}
	return (0);
}

void	exe_b_cmd(char *command_name,
			char **arguments, t_data **data, t_command *temp)
{
	if (ft_strcmp(command_name, "echo") == 0)
		ft_echo(arguments, data);
	else if (ft_strcmp(command_name, "cd") == 0)
		ft_cd(arguments, data);
	else if (ft_strcmp(command_name, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command_name, "exit") == 0)
	{
		if ((*data)->count_pipes >= 1)
		{
			free((*data)->command->cmd_path);
			free((*data)->pipe_end);
			(*data)->command = temp;
		}
		ft_exit(data, arguments);
	}
	else if (strcmp(arguments[0], "export") == 0)
		ft_export(data, arguments);
	else if (strcmp(arguments[0], "unset") == 0)
		ft_unset(arguments, data);
	else if (strcmp(arguments[0], "env") == 0)
		ft_env(arguments, data);
}

void	exec_one_cmd(t_data **data, t_command *command)
{
	int	fd;

	fd = 3;
	if (run_in_parent(data, command))
		return ;
	if (get_pid(command) == 0)
	{
		command->cmd_path = find_fullpath(data, command, &command->cmd_path);
		fd = open_fd(command);
		if (fd == 1)
			run_cmd(data, command, &command->cmd_path, command);
		if (fd == 0 || fd == -1)
		{
			free(command->cmd_path);
			free_memory(data, 1);
			exit(EXIT_FAILURE);
		}
	}
	wait_child_process(data, 0);
}
