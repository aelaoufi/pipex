/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:19:51 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/03/14 18:12:28 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (0);
	ft_bzero(str, count * size);
	return (str);
}

size_t	ft_strlen(const char *str)
{	
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *dst, size_t n)
{
	int	i;

	i = 0;
	while ((size_t)i < n)
	{
		((char *)dst)[i] = 0;
		i++;
	}
}
