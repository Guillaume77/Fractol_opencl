/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 18:45:24 by gubourge          #+#    #+#             */
/*   Updated: 2017/01/24 17:05:22 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_base_to(int nb, char *base_to)
{
	char	*dest;
	int		count;
	int		i;
	int		cp;

	i = 0;
	cp = nb;
	count = 0;
	while (cp > 0)
	{
		cp /= ft_strlen(base_to);
		count++;
	}
	if ((dest = malloc(sizeof(char) * (count + 2))) == NULL)
		return (NULL);
	while (nb > 0)
	{
		dest[i] = base_to[nb % ft_strlen(base_to)];
		nb /= ft_strlen(base_to);
		++i;
	}
	dest[i] = 0;
	return (ft_strrev(dest));
}

char		*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		length;
	int		nb;
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = 0;
	length = ft_strlen(nbr);
	nb = 0;
	while (nbr[++i])
	{
		while (nbr[i] != base_from[j])
			++j;
		nb += j * ft_power(ft_strlen(base_from), --length);
		j = 0;
	}
	dest = ft_base_to(nb, base_to);
	if (dest[0] == 0)
	{
		dest[0] = '0';
		dest[1] = 0;
	}
	return (dest);
}
