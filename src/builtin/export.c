/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:37:10 by Degef             #+#    #+#             */
/*   Updated: 2023/07/27 15:15:29 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cont(t_data **data, char **args, int i, int j)
{
	if (!len_char(args[i], '='))
		return ;
	free((*data)->env[j]);
	(*data)->env[j] = ft_strdup(args[i]);
}

void	export_value(char **args, int i, t_data **data)
{
	char	**aux;
	int		j;

	j = 0;
	while ((*data)->env[j]
		&& ft_strncmp((*data)->env[j], args[i], len_char(args[i], '=')))
		j++;
	if (!(*data)->env[j])
	{
		aux = copy_env((*data)->env, 1);
		if ((args[i][0] == '\"' && args[i][ft_strlen(args[i]) - 1] == '\"' )
			|| (args[i][0] == '\'' && args[i][ft_strlen(args[i]) - 1] == '\''))
			aux[j] = ft_substr(args[i], 1, ft_strlen(args[i]) - 2);
		else
			aux[j] = ft_strdup(args[i]);
		free_double_array(&(*data)->env);
		(*data)->env = copy_env(aux, 0);
		free_double_array(&aux);
	}
	else
		cont(data, args, i, j);
}

static void	display_error(char *str, t_data **data)
{
	ft_printf("`%s'", str);
	ft_putstr_fd(": not a valid identifier\n", 2);
	(*data)->exit_status = 1;
}

int	handle_export_errors(char **arg, int i, t_data **data)
{
	size_t	j;

	j = 0;
	while (arg[++i])
	{
		j = 0;
		if (!ft_strcmp(arg[i], "=") || (arg[i][0] == '='))
			return (display_error(arg[i], data), 1);
		while (ft_strlen(arg[i]) > j)
		{
			if (ft_strlen(arg[i]) > j && arg[i][j] == '\'')
				j = len_if_quote(arg[i], j, '\'');
			if (ft_strlen(arg[i]) > j && arg[i][j] == '\"')
				j = len_if_quote(arg[i], j, '\"');
			if (strlen(arg[i]) > j && !ft_isalnum(arg[i][j]) && arg[i][j] != '_'
				&& arg[i][j] != '=' && arg[i][j] != '\'' && arg[i][j] != '\"')
				return (display_error(arg[i], data), 1);
			if (j == 0 && (ft_isdigit(arg[i][j])))
				return (display_error(arg[i], data), 1);
			if (ft_strlen(arg[i]) <= j)
				return (0);
			j++;
		}
	}
	return (0);
}

void	ft_export(t_data **data, char **arguments)
{
	int	i;

	i = -1;
	if (arguments[1] == NULL)
	{
		sort_envp(data, '=');
		put_envp((*data)->env_sorted, data, i);
		free_double_array(&(*data)->env_sorted);
		(*data)->env_sorted = NULL;
	}
	else
	{
		if (handle_export_errors(arguments, 0, data))
			return ;
		i = 0;
		while (arguments[++i])
			export_value(arguments, i, data);
	}
}
