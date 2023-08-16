/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:52:32 by Degef             #+#    #+#             */
/*   Updated: 2023/07/25 20:00:57 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_if_capital(t_token *token, char **t_splitted, int t_count)
{
	if (ft_strcmp(ft_tolower(t_splitted[t_count]), "echo") == 0)
	{
		free((*token).value);
		(*token).value = ft_strdup("echo");
		(*token).type = B_COMMAND;
	}
	else if (ft_strcmp(ft_tolower(t_splitted[t_count]), "env") == 0)
	{
		free((*token).value);
		(*token).value = ft_strdup("env");
		(*token).type = B_COMMAND;
	}
	else if (!ft_strcmp(ft_tolower(t_splitted[t_count]), "pwd") && !t_count)
	{
		free((*token).value);
		(*token).value = ft_strdup("pwd");
		(*token).type = B_COMMAND;
	}
	else
		(*token).type = UNKNOWN;
}

void	get_token_type(t_token *token, char **t_splitted, int t_count)
{
	if (ft_strcmp(t_splitted[t_count], ">") == 0)
		(*token).type = GREAT;
	else if (ft_strcmp(t_splitted[t_count], "<") == 0)
		(*token).type = LESS;
	else if (ft_strcmp(t_splitted[t_count], ">>") == 0)
		(*token).type = GREAT_GREAT;
	else if (ft_strcmp(t_splitted[t_count], "<<") == 0)
		(*token).type = LESS_LESS;
	else if (t_count >= 1 && !ft_strcmp(t_splitted[t_count - 1], "<<"))
		(*token).type = DELIMITER;
	else if (t_splitted[t_count][0] == '|')
		(*token).type = PIPE;
	else if (ft_strcmp(t_splitted[t_count], "echo") == 0
		|| ft_strcmp(t_splitted[t_count], "cd") == 0
		|| ft_strcmp(t_splitted[t_count], "pwd") == 0
		|| ft_strcmp(t_splitted[t_count], "export") == 0
		|| ft_strcmp(t_splitted[t_count], "unset") == 0 
		|| ft_strcmp(t_splitted[t_count], "env") == 0 
		|| ft_strcmp(t_splitted[t_count], "exit") == 0)
		(*token).type = B_COMMAND;
	else
		check_if_capital(token, t_splitted, t_count);
}

void	build_tokens(t_data **data)
{
	t_token	*tokens;
	int		t_count;
	char	**t_splitted;
	t_token	token;

	t_splitted = split_input((*data)->mod_input, ' ');
	t_count = get_double_pointer_len(t_splitted);
	tokens = ft_calloc((t_count + 1), sizeof(t_token));
	t_count = -1;
	while (t_splitted[++t_count])
	{
		token.value = ft_strdup(t_splitted[t_count]);
		get_token_type(&token, t_splitted, t_count);
		tokens[t_count].t_len = get_double_pointer_len(t_splitted);
		tokens[t_count].value = token.value;
		tokens[t_count].type = token.type;
	}
	free_double_array(&t_splitted);
	(*data)->tokens = tokens;
}
