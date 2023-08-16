/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:19:08 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 20:22:23 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	write_string(char **args, int j, int i)
{
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	i = 0;
	while (args[j][i])
	{
		if ((args[j][i] == '\'' && double_quote == false))
			single_quote = !single_quote;
		else if (args[j][i] == '\"' && single_quote == false)
			double_quote = !double_quote;
		else
			printf("%c", args[j][i]);
		i++;
	}
}

static void	cont(char **args, int i, int k, int flag)
{
	if (!args[1])
	{
		g_exit_status = 0;
		printf("\n");
		return ;
	}
	if (args[1][0] == '-' && args[1][1] == 'n')
	{
		i = 2;
		flag = 1;
	}
	while (args[i])
	{
		if (i > 2 || (i > 1 && !flag))
			printf(" ");
		write_string(args, i, k);
		i++;
	}
	if (!flag)
		printf("\n");
	g_exit_status = 0;
}

void	ft_echo(char **args, t_data **data)
{
	int		i;
	int		k;
	int		flag;

	i = 1;
	flag = 0;
	k = 0;
	cont(args, i, k, flag);
	(*data)->exit_status = g_exit_status;
}
