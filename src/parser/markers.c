/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:13:15 by Degef             #+#    #+#             */
/*   Updated: 2023/08/14 22:19:54 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*This function has similar task with the below mark_commands function 
but this checks the error in the file*/
void	update_hasfile_err(t_command **cmd)
{
	t_command	*temp;

	temp = (*cmd);
	while ((*cmd))
	{
		if (((*cmd)->input.type == LESS 
				|| (*cmd)->input.type == LESS_LESS)
			&& access((*cmd)->input.filename, R_OK) == -1)
			(*cmd)->has_file_err = true;
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = temp;
}

/*this function is for marking a cmd struct as valid or invalid. 
It does this by checking if the command name is real cmd or not.
This mark will be used in the open_fd function to not let the executor 
cotinue after opening required files*/
void	mark_commands(t_data **data)
{
	t_command	*temp;
	int			return_value;

	temp = (*data)->command;
	return_value = 0;
	while ((*data)->command)
	{
		if (!(*data)->command->name)
		{
			(*data)->command = (*data)->command->next;
			continue ;
		}
		else if (ft_strchr((*data)->command->name, '/'))
			return_value = 
				is_cmd_executable_without_perror((*data)->command->name);
		else if (is_builtin((*data)->command->name))
			return_value = 1;
		else
			return_value = 
				find_command_without_perror(data, (*data)->command->name);
		if (return_value == -1 || return_value == -2)
			(*data)->command->is_runable = false;
		(*data)->command = (*data)->command->next;
	}
	(*data)->command = temp;
}
