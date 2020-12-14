/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cruiz-de <cruiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:23:27 by cruiz-de          #+#    #+#             */
/*   Updated: 2020/11/23 12:48:18 by cruiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char*)s;
	if (c == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&str[i]);
		i++;
	}
	if (s[i] == c)
		return (&str[i]);
	else
		return (0);
}
