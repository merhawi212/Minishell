/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separatecharacters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:00:06 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 11:18:52 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	separate(char **result, char *input, int *i, int *j)
{
	if (input[*i + 1] && input[*i + 1] == input[*i]
		&& (input[*i] == '>' || input[*i] == '<')) 
	{
		(*result)[++(*j)] = ' ';
		(*result)[++(*j)] = input[*i];
		(*result)[++(*j)] = input[*i];
		(*result)[++(*j)] = ' ';
		(*i)++;
	}
	else
	{
		(*result)[++(*j)] = ' ';
		(*result)[++(*j)] = input[*i];
		(*result)[++(*j)] = ' ';
	}
}

void	separate_characters_utils(char *input, int *i, int *j, char **result)
{
	int	inside_quote;

	inside_quote = 0;
	if (input[*i] && (input[*i] == '\"' || input[*i] == '\''))
	{
		inside_quote = input[*i];
		(*result)[++(*j)] = input[*i];
		while (input[++(*i)] && input[(*i)] != inside_quote)
		{
			(*result)[++(*j)] = input[*i];
		}
		if (input[*i] == inside_quote)
			(*result)[++(*j)] = input[*i];
	}
	else if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
		separate(result, input, i, j);
	else
		(*result)[++(*j)] = input[*i];
}

int	separate_characters(t_data **data, char	**input)
{
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = -1;
	result = ft_calloc(ft_strlen(*input) * 3 + 1, sizeof(char));
	while ((*input)[++i])
		separate_characters_utils(*input, &i, &j, &result);
	free(*input);
	(*data)->mod_input = result;
	return (1);
}

	// printf("separator result: %s\n", result);