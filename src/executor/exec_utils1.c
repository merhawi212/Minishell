/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:11:16 by Degef             #+#    #+#             */
/*   Updated: 2023/07/25 20:11:17 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *command_name)
{
	if (!command_name)
		return (0);
	if (!ft_strcmp(command_name, "echo")
		|| !ft_strcmp(command_name, "cd")
		|| !ft_strcmp(command_name, "pwd")
		|| !ft_strcmp(command_name, "export")
		|| !ft_strcmp(command_name, "unset")
		|| !ft_strcmp(command_name, "env")
		|| !ft_strcmp(command_name, "exit"))
		return (1);
	else
		return (0);
}

char	*find_fullpath(t_data **data, t_command *command, char **full_path)
{
	int		i;

	if (!command->name)
		return (0);
	i = -1;
	if (ft_strchr((*data)->command->name, '/'))
	{
		if (access(((*data)->command->name), X_OK) == 0)
			return (ft_strdup((*data)->command->name));
	}
	else 
	{
		while ((*data)->splitted_path[++i] != NULL)
		{
			(*full_path) = get_full_path((*data)->splitted_path[i],
					command->name, (*full_path));
			if (access((*full_path), X_OK) == 0)
			{
				return ((*full_path));
			}
			free((*full_path));
		}
	}
	return (0);
}

int	get_pid(t_command *cmd)
{
	int	pid;

	child_signals(cmd);
	pid = fork();
	if (pid < 0)
	{
		perror("pid error");
		exit(4);
	}
	return (pid);
}

void	ft_create_pipe(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->count_pipes)
	{
		if (pipe((*data)->pipe_end + (2 * i)) < 0)
		{
			perror("pipe error");
			exit(1);
		}
		i++;
	}
}

void	close_pipes(t_data **data, int i)
{
	i = 2 * i + 1;
	while (i >= 0)
	{
		close((*data)->pipe_end[i]);
		i--;
	}
}
