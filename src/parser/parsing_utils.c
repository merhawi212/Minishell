/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:51:58 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 10:47:41 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*lstlast(t_command *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	get_double_pointer_len(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

bool	handle_unclosed_quotes(t_data **data)
{
	bool	flag1;
	bool	flag2;
	int		i;

	flag1 = false;
	flag2 = false;
	i = -1;
	while ((*data)->input[++i])
	{
		if ((*data)->input[i] == '\'' && !flag2)
			flag1 = !flag1;
		else if ((*data)->input[i] == '\"' && !flag1)
			flag2 = !flag2;
	}
	if (flag1 || flag2)
	{
		printf(" \e[0;31mError! unclosed quote\n\033[0m");
		free((*data)->input);
		free((*data)->mod_input);
		if ((*data)->path)
			free((*data)->path);
		(*data)->exit_status = 2;
	}
	return (flag1 || flag2);
}

int	all_space(char *input, t_data **data)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == 32 || (input[i] >= 9 && input[i] <= 13)))
		i++;
	if (!input[i])
	{
		free((*data)->input);
		return (1);
	}
	return (0);
}

void	print_error2(char *s1, char *s2, char *s3)
{
	int	flag;

	flag = 0;
	if ((s2[0] == '\"' && s2[ft_strlen(s2) - 1] == '\"')
		|| (s2[0] == '\'' && s2[ft_strlen(s2) - 1] == '\''))
	{
		s2 = ft_substr(s2, 1, ft_strlen(s2) - 2);
		flag = 1;
	}
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	if (flag)
		free(s2);
}
