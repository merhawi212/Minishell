/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:19:21 by Degef             #+#    #+#             */
/*   Updated: 2023/07/25 20:19:22 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	put_envp(char **env, t_data **data, int i)
{
	int		j;
	bool	equal_sign;

	while (env[++i] && (*data))
	{
		equal_sign = false;
		j = -1;
		printf("declare -x ");
		while (env[i][++j])
		{
			if (env[i][j] == '=' && equal_sign == false)
			{
				printf("=\"");
				equal_sign = true;
			}
			else 
				printf("%c", env[i][j]);
		}
		if (equal_sign && !env[i][j])
			printf("\"\n");
		else
			printf("\n");
	}
}

int	len_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!cpy)
		return (0);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
}

void	sort_envp(t_data **data, char c)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	(*data)->env_sorted = copy_env((*data)->env, 0);
	while ((*data)->env_sorted[i] && (*data)->env_sorted[i + 1])
	{
		len = len_char((*data)->env_sorted[i], c);
		if (len_char((*data)->env_sorted[i], c) < 
			len_char((*data)->env_sorted[i + 1], c))
			len = len_char((*data)->env_sorted[i], c);
		if (ft_memcmp((*data)->env_sorted[i],
				(*data)->env_sorted[i + 1], len) > 0)
		{
			tmp = (*data)->env_sorted[i];
			(*data)->env_sorted[i] = (*data)->env_sorted[i + 1];
			(*data)->env_sorted[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}
