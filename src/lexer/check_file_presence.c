/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_presence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:16:09 by Degef             #+#    #+#             */
/*   Updated: 2023/08/07 20:38:56 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cont3(char *str, char **trimed, int count_pipes)
{
	int	fd;

	(void)count_pipes;
	fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (fd == -1)
	{
		print_error("minishell: ", str, ": ");
		close(fd);
		free(*trimed);
		return (0);
	}
	close(fd);
	return (1);
}

int	cont2(char *str, char **trimed, int count_pipes, bool *is_pipe)
{
	if (count_pipes >= 1 && (*is_pipe == TRUE))
	{
		*is_pipe = FALSE;
		free(*trimed);
		return (print_error("minishel: ", str, ": "), 1);
	}
	else if (count_pipes == 0)
	{
		free(*trimed);
		return (print_error("minishell: ", str, ": "), 0);
	}
	free(*trimed);
	return (1);
}

int	cont1(char *str, int count_pipes, bool *is_pipe)
{
	if (count_pipes >= 1 && *is_pipe == TRUE)
	{
		*is_pipe = FALSE;
		return (print_error("minishell: ", str, ": "), 1);
	}
	else if (count_pipes == 0)
		return (print_error("minishell: ", str, ": "), 0);
	return (1);
}

int	is_directory(int count_pipes, char *str, t_token_type type, bool *is_pipe)
{
	char	*trimed;

	if (type == LESS && access(str, R_OK) == -1)
		return (cont1(str, count_pipes, is_pipe));
	trimed = trim_dir_from_back(str);
	if (ft_strchr(str, '/') && (type == GREAT || type == GREAT_GREAT)
		&& access(trimed, F_OK) == -1)
		return (cont2(str, &trimed, count_pipes, is_pipe) == 1);
	else if (type == GREAT || type == GREAT_GREAT)
		if (cont3(str, &trimed, count_pipes) == 0)
			return (0);
	free(trimed);
	return (1);
}

int	check_dir_existance(t_data **data, t_token *tokens, int i, char *str)
{
	bool	is_pipe;

	is_pipe = TRUE;
	while (++i < tokens[0].t_len - 1)
	{
		if (tokens[i].type == PIPE)
			is_pipe = TRUE;
		if (tokens[i].type == LESS || tokens[i].type == GREAT
			|| tokens[i].type == GREAT_GREAT)
		{
			str = remove_quote_and_cwd_indicator(data, i);
			if (!is_directory((*data)->count_pipes, str,
					tokens[i].type, &is_pipe))
			{
				free(str);
				perror_free(data, " ", " ", 1);
				return (0);
			}
			free((*data)->tokens[i + 1].value);
			(*data)->tokens[i + 1].value = str;
			i++;
		}
	}
	return (1);
}
