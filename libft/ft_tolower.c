/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <Degei411233@outlook.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 16:35:44 by mkiflema          #+#    #+#             */
/*   Updated: 2023/07/21 16:38:25 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_tolower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = (str[i] + 32);
	}
	return (str);
}

// int main()
// {
// 	char c = 'Z';
// 	printf("%c", tolower(c));
// 	printf("\n%c", ft_tolower(c));
// }