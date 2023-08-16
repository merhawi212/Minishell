/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:19:28 by Degef             #+#    #+#             */
/*   Updated: 2023/07/27 18:42:26 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	ft_env(char **arg, t_data **data)
{
	int	i;

	if (arg[1] != NULL)
	{
		print_error2("env: ", arg[1], ": No such file or directory\n");
		(*data)->exit_status = 127;
		return ;
	}
	i = -1;
	while ((*data)->env[++i])
	{
		if (ft_strchr((*data)->env[i], '='))
			printf(" %s\n", (*data)->env[i]);
	}
}
