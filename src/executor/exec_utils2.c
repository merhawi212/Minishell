/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:02:44 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 22:07:44 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_child_process(t_data **data, int status)
{
	int	i;

	i = -1;
	while ((++i < ((*data)->count_pipes + 1)))
	{
		wait(&status);
		if (WIFEXITED(status))
			(*data)->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			if (status != 13)
				(*data)->exit_status = 128 + WTERMSIG(status);
	}
	return ((*data)->exit_status);
}

void	print_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	perror("");
}

void	display_file_error_msg(t_command *command, int token_type, int fd)
{
	if (token_type == LESS && fd == -1)
	{
		if (command->input.filename[
				ft_strlen(command->input.filename) - 1] == '/')
			print_error("minishell: ", command->input.filename, ": ");
	}
	if ((token_type == GREAT_GREAT || token_type == GREAT) && fd == -1)
	{
		if (command->output.filename[
				ft_strlen(command->output.filename) - 1] == '/')
			print_error("minishell: ", command->output.filename, ": ");
	}
}

int	get_fd(t_command *command, int token_type)
{
	int	fd;

	fd = 0;
	if (token_type == GREAT)
		fd = open(command->output.filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (token_type == GREAT_GREAT)
		fd = open(command->output.filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (token_type == LESS)
		fd = open(command->input.filename, O_RDONLY, 0777);
	display_file_error_msg(command, token_type, fd);
	return (fd);
}
