/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:51:17 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 20:05:49 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	print_command(const t_command *command)
// {
// 	while (command)
// 	{
// 		printf("Command Name: %s\n", command->name);
// 		printf("Arguments:\n");
// 		for (int i = 0; command->arguments[i] != NULL; i++)
// 		{
// 			printf("- %s\n", command->arguments[i]);
// 		}
// 		printf("Input: %s\n", command->input.name);
// 		printf("Output: %s\n", command->output.name);
// 		printf("Delimiter/input filename: %s\n", command->input.filename);
// 		printf("Delimiter/output filename: %s\n", command->output.filename);
// 		printf("input type: %d\n", command->input.type);
// 		printf("output type: %d\n", command->output.type);
// 		printf("is runable: %d\n", command->is_runable);
// 		printf("has file an error: %d\n", command->has_file_err);
// 		command = command->next;
// 	}
// }

void	check_exit_status(t_data **data)
{
	if (g_exit_status != -2)
	{
		(*data)->exit_status = g_exit_status;
		g_exit_status = -2;
	}
}

int	init(t_data **data)
{
	int	i;

	(*data)->input = readline("\033[0;33mminishell ~$ \033[0m");
	if ((*data)->input == NULL)
	{
		free((*data)->input);
		free_double_array(&(*data)->env);
		free (*data);
		printf("exit\n");
		exit(0);
	}
	check_exit_status(data);
	if (all_space((*data)->input, data))
		return (0);
	add_history((*data)->input);
	(*data)->mod_input = ft_strdup((*data)->input);
	(*data)->command = NULL;
	(*data)->count_pipes = 0;
	(*data)->input_fd = -1;
	(*data)->path = NULL;
	i = -1;
	while ((*data)->env[++i])
		if (ft_strncmp((*data)->env[i], "PATH", 4) == 0)
			(*data)->path = strdup((*data)->env[i]);
	return (1);
}

void	routine(t_data **data)
{
	while (1)
	{
		handle_signals();
		if (!init(data))
			continue ;
		if (!(*data)->mod_input[0])
			continue ;
		if (handle_unclosed_quotes(data))
			continue ;
		remove_extra_spaces(&(*data)->mod_input, data);
		remove_unnecessary_quote(data);
		separate_characters(data, &(*data)->mod_input);
		if (!expand(data))
			continue ;
		if (!lex(data))
			continue ;
		if (!parser(data))
			continue ;
		if (!check_here_doc(data))
			continue ;
		// print_command((*data)->command);
		handle_exc(data);
		free_memory(data, 0);
	}
}

void	increment_shlvl(t_data **data)
{
	int		i;
	char	*num;
	char	*sub;
	char	*new_shlvl;

	i = -1;
	sub = NULL;
	while ((*data)->env[++i])
	{
		if (!ft_strncmp((*data)->env[i], "SHLVL", 5))
		{
			sub = ft_substr((*data)->env[i], 6, 2);
			num = ft_itoa(ft_atoi(sub) + 1);
			new_shlvl = ft_strjoin(ft_strdup("SHLVL="), num);
			free((*data)->env[i]);
			(*data)->env[i] = new_shlvl;
			free(sub);
			free(num);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;

	if (argc != 1)
		return (1);
	(void)argv;
	data = (t_data *)malloc(sizeof(t_data));
	data->env = copy_env(envp, 0);
	increment_shlvl(&data);
	data->exit_status = 0;
	g_exit_status = -2;
	routine(&data);
	return (0);
}
