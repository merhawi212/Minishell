/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:02:24 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 10:56:30 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_double_array(char ***str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		free((*str)[i]);
	free(*str);
}

void	free_tokens(t_data **data)
{
	int	t_len;
	int	i;

	t_len = (*data)->tokens[0].t_len;
	i = -1;
	while (++i < t_len && (*data)->tokens[i].value)
		free((*data)->tokens[i].value);
	free((*data)->tokens);
}

void	free_command(t_command *command)
{
	t_command	*next;

	while (command)
	{
		next = command->next;
		if (command->name)
			free(command->name);
		free(command->input.name);
		free(command->output.name);
		free(command->input.filename);
		free(command->output.filename);
		if (command->arguments != NULL)
			free_double_array(&command->arguments);
		free(command);
		command = next;
	}
}

void	free_memory(t_data **data, int free_env)
{
	unlink("libft/here_doc_temp");
	unlink("libft/here_doc_sig");
	free((*data)->input);
	free((*data)->mod_input);
	if ((*data)->path)
		free((*data)->path);
	if ((*data)->splitted_path)
		free_double_array(&(*data)->splitted_path);
	free_tokens(data);
	free_command((*data)->command);
	if (free_env)
	{
		free_double_array(&(*data)->env);
		free(*data);
	}
}
