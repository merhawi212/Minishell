/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:51:49 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 13:19:17 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cont(t_data **data, int *i, t_command *cmd, t_token_type type)
{
	if (type == GREAT || type == GREAT_GREAT)
	{
		free(cmd->output.name);
		cmd->output.name = ft_strdup("file");
		cmd->output.type = GREAT;
		if (type == GREAT_GREAT)
			cmd->output.type = GREAT_GREAT;
		if (cmd->output.filename)
			free(cmd->output.filename);
		cmd->output.filename
			= ft_strdup((*data)->tokens[++(*i)].value);
	}
}

void	if_output_ri(t_data **data, int *i, t_command *cmd, t_token_type type)
{
	if ((*i) == 0 || (*data)->tokens[*i - 1].type == PIPE)
	{
		free(cmd->name);
		if (type == GREAT || type == GREAT_GREAT
			|| type == LESS || type == LESS_LESS)
		{
			if ((*data)->tokens[*i + 1].value && (*data)->tokens[*i + 2].value
				&& (*data)->tokens[*i + 2].type != PIPE
				&& (*data)->tokens[*i + 2].type != GREAT
				&& (*data)->tokens[*i + 2].type != GREAT_GREAT)
				cmd->name = ft_strdup((*data)->tokens[*i + 2].value);
			else 
				cmd->name = NULL;
		}
	}
	cont(data, i, cmd, type);
}

// Function to check if a string is enclosed in quotes and remove the quotes
char	*remove_quotes(const char	*str, t_command *cmd)
{
	int		len;
	char	*result;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')))
	{
		cmd->input.is_delimiter_in_quote = true;
		result = ft_substr(str, 1, len - 2);
		return (result);
	}
	else
		return (ft_strdup(str));
}

void	if_here_doc(t_command *cmd, t_data **data, int *i)
{
	free(cmd->input.name);
	cmd->input.name = ft_strdup("here_doc");
	cmd->input.type = LESS_LESS;
	(*i)++;
	if (cmd->input.filename)
		free(cmd->input.filename);
	cmd->input.filename = remove_quotes((*data)->tokens[*i].value, cmd);
}

void	identify_redirections(t_data **data, int *i)
{
	t_token_type	type;
	t_command		*cmd;

	type = (*data)->tokens[*i].type;
	cmd = lstlast((*data)->command);
	if_output_ri(data, i, cmd, type);
	if (type == LESS)
	{
		free(cmd->input.name);
		cmd->input.name = ft_strdup("file");
		cmd->input.type = LESS;
		(*i)++;
		if (cmd->input.filename)
			free(cmd->input.filename);
		cmd->input.filename = NULL;
		cmd->input.filename = ft_strdup((*data)->tokens[*i].value);
	}
	else if (type == LESS_LESS)
		if_here_doc(cmd, data, i);
}
