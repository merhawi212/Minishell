/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:52:42 by Degef             #+#    #+#             */
/*   Updated: 2023/07/26 21:22:03 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_if_quote(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	i++;
	return (i);
}

static int	count_strings(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
			j++;
		if (s[i] == '\'')
			i = len_if_quote(s, i, '\'');
		else if (s[i] == '\"')
			i = len_if_quote(s, i, '\"');
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

static char	*ft_word(char *str, char c)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	if (str[len] && (str[len] == '\''))
		len = len_if_quote(str, len, '\'');
	else if (str[len] && (str[len] == '\"'))
		len = len_if_quote(str, len, '\"');
	while (str[len] && str[len] != c)
		len++;
	word = ft_calloc((len + 1), sizeof(char));
	i = -1;
	while (++i < len)
		word[i] = str[i];
	return (word);
}

static void	split(char *str, int i, char ***strings, char c)
{
	char	quote;

	while (*str != '\0')
	{
		while (*str != '\0' && *str == c)
			str++;
		if (*str != '\0')
			(*strings)[i++] = ft_word(str, c);
		if (*str && (*str == '\'' || *str == '\"'))
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
			if (*str == quote)
				str++;
		}
		while (*str && *str != c)
			str++;
	}
	(*strings)[i] = 0;
}

char	**split_input(char *str, char c)
{
	char	**strings;
	int		i;

	i = 0;
	if (!str)
		return (0);
	strings = malloc((count_strings(str, c) + 1) * sizeof(char *));
	if (!strings)
		return (0);
	split(str, i, &strings, c);
	return (strings);
}
