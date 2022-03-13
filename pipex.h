/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:51:10 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/03/13 15:13:14 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
#include <sys/wait.h>

int			ft_strncmp(const char *s1, const char *s2, size_t n);
static int	ft_nmbofwrds(char *str, char c);
static char	**wordsplit(const char *s, char c, char **str, int i);
char		**ft_split(char const *s, char c);
char		*find_path(char **env);
void		exec_path(char **env, char *cmd);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *str);
void		ft_bzero(void *dst, size_t n);

#endif