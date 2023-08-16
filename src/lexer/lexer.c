/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkiflema <mkiflema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:53:14 by Degef             #+#    #+#             */
/*   Updated: 2023/07/29 22:09:44 by mkiflema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void printTokens(const t_token* tokens, int tokenCount) {
//     for (int i = 0; i < tokenCount; i++) {
//         printf("Token Type: %d, Value: %s, Token Length: %d\n",
//                tokens[i].type, tokens[i].value, tokens[i].t_len);
//     }
// }

char	*trim_dir_from_back(char *value)
{
	int	str_len;

	str_len = ft_strlen(value);
	while (str_len > 0 && value[--str_len] != '/')
		continue ;
	return (ft_substr(value, 0, str_len));
}

char	*remove_quote_and_cwd_indicator(t_data **data, int i)
{
	char	*str;
	char	*temp;

	str = ft_strdup((*data)->tokens[i + 1].value);
	if ((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		|| (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"'))
	{
		free(str);
		str = ft_substr((*data)->tokens[i + 1].value, 1,
				ft_strlen((*data)->tokens[i + 1].value) - 2);
	}
	if (ft_strncmp(str, "./", 2) == 0)
	{
		temp = ft_substr(str, 2, ft_strlen(str) - 2);
		free(str);
		str = temp;
	}
	return (str);
}

void	count_pipes(t_data **data, t_token *tokens)
{
	int	i;

	i = -1;
	while (++i < tokens[0].t_len)
		if (tokens[i].type == PIPE)
			(*data)->count_pipes++;
}

	// printTokens((*data)->tokens, (*data)->tokens[0].t_len);
// Lexical analysis function
int	lex(t_data **data)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	build_tokens(data);
	count_pipes(data, (*data)->tokens);
	if (!check_syntax_error(data, (*data)->tokens, (*data)->tokens[0].t_len))
		return (0);
	if (!check_dir_existance(data, (*data)->tokens, i, str))
	{
		(*data)->exit_status = 1;
		return (0);
	}
	return (1);
}
