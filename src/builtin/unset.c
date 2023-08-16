/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:08:27 by Degef             #+#    #+#             */
/*   Updated: 2023/07/25 20:19:03 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_unset_errors(char **arg, int i)
{
	int	j;

	j = 0;
	if (arg[1] == NULL)
		return (1);
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i][j]) && arg[i][j] != '_' && arg[i][j] != '=')
		{
			fprintf(stderr,
				"Error: Invalid character '%c' in unset argument\n", arg[i][j]);
			return (1);
		}
		if (ft_isdigit(arg[1][0]))
		{
			fprintf(stderr, "Error: Argument starts with a digit\n");
			return (1);
		}
	}
	return (0);
}

void	unset_var(int j, int k, t_data **data)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while ((*data)->env[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len));
	if (!cpy)
		return ;
	i = -1;
	k = 0;
	while (++i < len)
	{
		if (i != j)
			cpy[k++] = ft_strdup((*data)->env[i]);
	}
	free_double_array(&(*data)->env);
	(*data)->env = cpy;
}

void	ft_unset(char **args, t_data **data)
{
	int	i;
	int	j;

	if (handle_unset_errors(args, 0))
		return ;
	i = 0;
	while (args[++i])
	{
		j = -1;
		while ((*data)->env[++j])
		{
			if (!(ft_strncmp(args[i], (*data)->env[j], ft_strlen(args[i]))))
			{
				unset_var(j, i, data);
				break ;
			}
		}
	}
}
