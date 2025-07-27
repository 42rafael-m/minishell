/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:10:20 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 19:36:49 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ESC_CHARS "\\\'\"\?abfnrtv"

static int	ft_len(char *s)
{
	int	r;
	int	i;

	r = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\\' && ft_strchr(ESC_CHARS, s[i + 1]))
			i++;
		r++;
		i++;
	}
	return (r);
}

char	*ft_esc_char(char *s)
{
	int		len;
	char	*r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	len = ft_len(s);
	r = (char *)ft_calloc(len + 1, sizeof(char));
	if (!r)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\\' && ft_strchr(ESC_CHARS, s[i]))
			r[j] = s[++i];
		else
			r[j] = s[i];
		i++;
		j++;
	}
	return (r);
}
