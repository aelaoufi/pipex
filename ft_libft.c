/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:05:10 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/03/14 18:12:34 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *)ft_calloc(sizeof(char ), ft_strlen(s2) + ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i] && (i < n - 1))
		i++;
	return ((unsigned char )s1[i] - (unsigned char )s2[i]);
}

static int	ft_nmbofwrds(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != c)
			count++;
		i++;
	}
	if (str[ft_strlen(str) - 1] != c && str[0] != '\0')
		count++;
	return (count);
}

static char	**wordsplit(const char *s, char c, char **str, int i)
{
	int	end;
	int	j;
	int	k;

	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			end = i;
			while (s[end] != c && s[end])
				end++;
			str[j] = (char *)ft_calloc(sizeof(char), end - i + 1);
			if (str[j] == NULL)
				return (NULL);
			k = 0;
			while (i < end)
				str[j][k++] = s[i++];
			j++;
		}
		if (s[i])
			i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char **)ft_calloc(sizeof(char *), ft_nmbofwrds((char *)s, c) + 1);
	if (str == NULL)
		return (NULL);
	str = wordsplit(s, c, str, i);
	return (str);
}
