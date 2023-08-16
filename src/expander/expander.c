/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:01:25 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 10:59:20 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*add_value(char *var_name, char *var, size_t i, char **arg)
{
	char	*result;
	int		end_of_var;
	size_t	j;

	result = ft_calloc((ft_strlen((*arg)) + ft_strlen(var) - i), sizeof(char));
	i = -1;
	while ((++i < (ft_strlen((*arg)) - ft_strlen(var_name)))
		&& (*arg)[i] != '$')
		result[i] = (*arg)[i];
	end_of_var = i + ft_strlen(var_name);
	i--;
	j = -1;
	while (++j < ft_strlen(var) && var[j])
		result[++i] = var[j];
	while ((*arg)[end_of_var++]
		&& (++i < ft_strlen((*arg)) - ft_strlen(var_name) + ft_strlen(var)))
		result[i] = (*arg)[end_of_var];
	free(*arg);
	return (result);
}

char	*find_var_name(char *result, size_t *i)
{
	char	*var_name;
	int		var_len;

	var_len = 0;
	(*i)++;
	var_name = NULL;
	while (result[*i] && ((result[*i] == '_')
			|| (result[*i] >= 'a' && result[*i] <= 'z')
			|| (result[*i] >= 'A' && result[*i] <= 'Z')
			|| (result[*i] == '?')))
	{
		(*i)++;
		var_len++;
		if (result[*i - 1] == '?')
			break ;
	}
	var_name = ft_substr(result, *i - var_len, var_len);
	return (var_name);
}

void	expand_variable(char **result, size_t *i, t_data **data)
{
	char	*var_name;
	char	*value;

	var_name = find_var_name(*result, i);
	if (!var_name)
		return ;
	value = search_value(var_name, data);
	*result = add_value(var_name, value, ft_strlen(var_name), result);
	*i = *i + ft_strlen(value) - ft_strlen(var_name) - 1;
	if (value)
		free(value);
	free(var_name);
}

char	*check_expansion(char *arg, t_data **data)
{
	size_t	i;
	char	*result;

	i = 0;
	result = ft_strdup(arg);
	while (result[i])
	{
		while (result[i] && ((result[i] != '$')
				|| (result[i] == '$' && result[i + 1] == ' ')
				|| (result[i] == '$' && !result[i + 1])))
		{
			if (result[i] == '\'')
				i = len_if_quote(result, i, '\'');
			i++;
		}
		if (result[i] && result[i] == '$')
			expand_variable(&result, &i, data);
	}
	return (result);
}

int	expand(t_data **data)
{
	char		*expanded_str;

	if (ft_strchr((*data)->mod_input, '$'))
	{
		expanded_str = check_expansion((*data)->mod_input, data);
		free((*data)->mod_input);
		(*data)->mod_input = expanded_str;
	}
	if (!(*data)->mod_input[0])
	{
		free((*data)->input);
		free((*data)->mod_input);
		if ((*data)->path)
			free((*data)->path);
		return (0);
	}
	if (replace_tilde_with_home(data))
		return (0);
	return (1);
}
