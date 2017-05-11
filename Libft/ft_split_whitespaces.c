/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/28 18:23:06 by gubourge          #+#    #+#             */
/*   Updated: 2017/04/06 12:15:10 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_nb_word(char *str)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			++i;
		if (str[i] != 0)
			++word;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
			++i;
	}
	return (word);
}

static int	ft_ultimate_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
		++i;
	return (i);
}

static char	*ft_ultimate_strdup(char *str)
{
	char	*dest;
	int		i;
	int		size;

	i = 0;
	size = ft_ultimate_strlen(str);
	if ((dest = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (i < size)
	{
		dest[i] = str[i];
		++i;
	}
	dest[i] = 0;
	return (dest);
}

static char	*ft_find_word(char *str, int *i)
{
	char	*word;

	while (str[*i])
	{
		while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
			++(*i);
		if (str[*i] != 0)
		{
			word = ft_ultimate_strdup(&str[*i]);
			while (str[*i] != ' ' && str[*i] != '\t' &&
			str[*i] != '\n' && str[*i])
				++(*i);
			return (word);
		}
	}
	return (NULL);
}

char		**ft_split_whitespaces(char *str)
{
	char	**tab;
	int		word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = ft_nb_word(str);
	if ((tab = (char **)malloc(sizeof(char *) * (word + 1))) == NULL)
		return (NULL);
	while (j < word)
	{
		if ((tab[j] = ft_find_word(str, &i)) == NULL)
			return (NULL);
		++j;
	}
	tab[j] = NULL;
	return (tab);
}
