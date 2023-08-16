/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_extra_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:52:58 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 13:51:26 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	if_quote(char **input, char **result, int *j, int *i)
{
	if ((*input)[*i] == '\'')
	{
		(*result)[(*j)++] = (*input)[*i];
		while ((*input)[++(*i)] != '\'')
			(*result)[(*j)++] = (*input)[*i];
		(*result)[(*j)++] = (*input)[*i];
		return (1);
	}
	else if ((*input)[*i] == '\"')
	{
		(*result)[(*j)++] = (*input)[*i];
		while ((*input)[++(*i)] != '\"')
			(*result)[(*j)++] = (*input)[*i];
		(*result)[(*j)++] = (*input)[*i];
		return (1);
	}
	return (0);
}

char	*remove_extra_space_util(char **input, char **result, int j)
{
	int		i;
	bool	prev_space;

	prev_space = false;
	i = -1;
	while ((*input)[++i] != '\0')
	{
		if (if_quote(input, result, &j, &i))
			continue ;
		else if ((*input)[i] == 32 || (*input)[i] == 9)
		{
			if (!prev_space)
			{
				(*result)[j++] = 32;
				prev_space = true;
			}
		}
		else
		{
			(*result)[j++] = (*input)[i];
			prev_space = false;
		}
	}
	return ((*result));
}

void	remove_extra_spaces(char	**input, t_data **data)
{
	char	*result;
	int		j;

	result = ft_calloc (ft_strlen(*input) + 1, sizeof(char));
	j = 0;
	result = remove_extra_space_util(input, &result, j);
	free(*input);
	(*data)->mod_input = result;
}
