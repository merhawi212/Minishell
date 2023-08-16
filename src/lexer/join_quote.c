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

void	copy_till_quote(char *str, char **result, int *i, int *j)
{
	while (str[*i] && str[*i] != '\"')
		(*result)[++(*j)] = str[(*i)++];
}

static void	cont(char ***arr, int *i, int *j, bool *quote)
{
	if ((*arr)[0][(*i)] && (*arr)[0][(*i)] == '\"' && (!(*arr)[0][(*i) + 1]
			|| (*arr)[0][(*i) + 1]) && (*arr)[0][(*i) + 1] != '\"')
	{
		((*arr)[1])[++(*j)] = (*arr)[0][(*i)++];
		*quote = !(*quote);
	}
	else if ((*arr)[0][(*i)] && (*arr)[0][(*i)] == '\"' && (!(*arr)[0][(*i) + 1]
			|| (*arr)[0][(*i) + 1]) && (*arr)[0][(*i) + 1] == '\"')
	{
		*i = *i + 2;
		copy_till_quote((*arr)[0], &(*arr)[1], i, j);
	}
}

void	remove_quote2(char ***arr, int i, bool quote)
{
	int	j;

	j = -1;
	while ((*arr)[0][i])
	{
		if ((*arr)[0][i] && (*arr)[0][i] == '\"')
		{
			if (!quote)
			{
				quote = !quote;
				((*arr)[1])[++j] = (*arr)[0][i++];
				copy_till_quote((*arr)[0], &(*arr)[1], &i, &j);
			}
			cont(arr, &i, &j, &quote);
		}
		else
			copy_till_quote((*arr)[0], &(*arr)[1], &i, &j);
	}
}

void	remove_unnecessary_quote(t_data **data)
{
	char	**arr;
	int		i;
	bool	quote_started;

	arr = ft_calloc(3, sizeof(char *));
	arr[0] = ft_strdup((*data)->mod_input);
	arr[1] = ft_calloc(ft_strlen(arr[0]) + 1, sizeof(char));
	i = 0;
	quote_started = false;
	remove_quote2(&arr, i, quote_started);
	free((*data)->mod_input);
	(*data)->mod_input = ft_strdup(arr[1]);
	free_double_array(&arr);
}
