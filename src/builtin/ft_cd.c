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

void	update_old_pwd(t_data **data, char *old_pwd)
{
	int	i;

	i = -1;
	while ((*data)->env[++i])
	{
		if (!ft_strncmp((*data)->env[i], "OLDPWD", 6))
		{
			free((*data)->env[i]);
			(*data)->env[i] = ft_strjoin(ft_strdup("OLDPWD="), old_pwd);
		}
	}
}

void	update_pwd(t_data **data, int i)
{
	char	cwd[1024];
	char	*old_pwd;

	while ((*data)->env[++i])
	{
		if (!ft_strncmp((*data)->env[i], "PWD", 3))
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				old_pwd = ft_substr((*data)->env[i], 4,
						ft_strlen((*data)->env[i]) - 4);
				free((*data)->env[i]);
				(*data)->env[i] = ft_strjoin(ft_strdup("PWD="), cwd);
			}
			else
			{
				perror("pwd");
				return ;
			}
		}
	}
	update_old_pwd(data, old_pwd);
	if (i > 0)
		free(old_pwd);
}

void	change_to_old_pwd(t_data **data)
{
	int		i;
	char	*old_pwd;

	i = -1;
	while ((*data)->env[++i])
	{
		if (!ft_strncmp((*data)->env[i], "OLDPWD", 6))
		{
			old_pwd = ft_substr((*data)->env[i], 7,
					ft_strlen((*data)->env[i]) - 6);
			printf("%s\n", old_pwd);
			if (old_pwd != NULL)
				chdir(old_pwd);
			else
				printf("cd: No home directory\n");
			free(old_pwd);
		}
	}
}

void	go_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home != NULL)
		chdir(home);
	else
		printf("cd: No home directory\n");
}

void	ft_cd(char **arguments, t_data **data)
{
	int	a;

	a = 0;
	if (!arguments[1] || (arguments[1][0] == '-' && arguments[1][1] == '-'))
		go_to_home();
	else if (get_double_pointer_len(arguments) > 2)
		return ;
	else if (arguments[1][0] == '-')
		change_to_old_pwd(data);
	else
	{
		a = chdir(arguments[1]);
		if (a != 0)
		{
			(*data)->exit_status = 1;
			return (print_error("cd: ", arguments[1], ": "));
		}
	}
	if (a == 0)
		update_pwd(data, -1);
}
