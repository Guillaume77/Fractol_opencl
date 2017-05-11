/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/24 16:26:53 by gubourge          #+#    #+#             */
/*   Updated: 2016/06/24 16:28:25 by gubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	char	dest[ft_strlen(str)];
	int		i;
	int		j;

	i = -1;
	while (str[++i])
		dest[i] = str[i];
	j = -1;
	while (--i >= 0)
		str[i] = dest[++j];
	return (str);
}
