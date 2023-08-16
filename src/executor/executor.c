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

int	is_cmd_dir(char *full_path)
{
	struct stat	sb;

	if (stat(full_path, &sb) == -1)
		return (print_error("minishell: ", full_path, ": "), 0);
	if (S_ISDIR(sb.st_mode))
	{
		return (print_error2("minishell: ", full_path, ": is a directory\n"), 0);
	}
	return (1);
}

void	run_cmd(t_data **data, t_command *command, char **full_path,
				t_command *temp_cmd)
{
	if (!command->name)
		return ;
	else if (is_builtin(command->name))
	{
		exe_b_cmd(command->name, command->arguments, data, temp_cmd);
		exit_from_child(data, temp_cmd, EXIT_SUCCESS);
	}
	else
	{
		if (is_cmd_dir(*full_path) == 0)
			exit_from_child(data, temp_cmd, 126);
		execve(*full_path, command->arguments, (*data)->env);
		exit_from_child(data, temp_cmd, EXIT_FAILURE);
	}
}

void	remove_qoutes(t_command **cmd)
{
	char		*str;
	t_command	*temp;
	int			i;

	temp = *cmd;
	while (*cmd)
	{
		i = -1;
		while ((*cmd)->arguments[++i] && !is_builtin((*cmd)->name))
		{
			str = ft_strdup((*cmd)->arguments[i]);
			if ((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
				|| (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"'))
			{
				free((*cmd)->arguments[i]);
				(*cmd)->arguments[i] = ft_substr(str, 1,
						ft_strlen(str) - 2);
			}
			free(str);
		}
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}

void	handle_exc(t_data **data)
{
	remove_qoutes(&(*data)->command);
	if ((!(*data)->command->next))
		exec_one_cmd(data, (*data)->command);
	else
		execute_multiple_cmd(data);
}
