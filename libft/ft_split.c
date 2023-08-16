/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:09:26 by marvin            #+#    #+#             */
/*   Updated: 2022/12/17 12:09:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_string_len(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
			j++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	if ((!s && !c) || !s)
		return (0);
	j = ft_string_len(s, c);
	result = (char **)malloc((j + 1) * sizeof(char *));
	if (!result)
		return (0);
	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			i = 0;
			while (*s != '\0' && *s != c && ++i)
				s++;
			result[j++] = ft_substr(s - i, 0, i);
		}
		else
			s++;
	}
	result[j] = 0;
	return (result);
}

// int main()
// {
// 	char *s="hello:world";
// 	char c = ':';
// 	char **result = ft_split(s, c);
// 	int i = 0;
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i++]);
// 		// printf("%d", i);
// 	}
// 	return (0);
// }
