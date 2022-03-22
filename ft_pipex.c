/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:45:50 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/03/19 15:55:30 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			return (*env + 5);
		env++;
	}
	perror("commande:");
	return (0);
}

void	exec_path(char **env, char *cmd)
{
	char	*patt;
	char	**paths;
	char	**cmds;
	int		i;

	i = 0;
	patt = find_path(env);
	paths = ft_split(patt, ':');
	cmds = ft_split(cmd, ' ');
	if (access(cmds[0], X_OK) == 0)
		execve(cmds[0], cmds, env);
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmds[0]);
		if (access(paths[i], X_OK) == 0)
			execve(paths[i], cmds, env);
		i++;
	}
	perror("Commande");
}

int	openpipe(char **av, t_var *p)
{
	p->inputfile = open(av[1], O_RDONLY);
	if (p->inputfile < 0)
	{
		perror(av[1]);
		exit(0);
	}
	p->outputfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->outputfile < 0)
		perror(av[4]);
	if (pipe(p->fd) == -1)
		return (1);
	return (0);
}

int	childprocess(char **env, char **av, t_var *p)
{
	p->pid1 = fork();
	if (p->pid1 < 0)
		return (2);
	if (p->pid1 == 0)
	{
		dup2(p->fd[1], STDOUT_FILENO);
		dup2(p->inputfile, STDIN_FILENO);
		close(p->fd[0]);
		close(p->fd[1]);
		exec_path(env, av[2]);
	}
	p->pid2 = fork();
	if (p->pid2 < 0)
		return (3);
	if (p->pid2 == 0)
	{
		dup2(p->fd[0], STDIN_FILENO);
		dup2(p->outputfile, STDOUT_FILENO);
		close(p->fd[0]);
		close(p->fd[1]);
		exec_path(env, av[3]);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_var	*p;

	if (ac != 5)
	{
		perror("Wrong number or arguments");
		return (0);
	}
	(void)ac;
	p = malloc(sizeof(t_var));
	openpipe(av, p);
	childprocess(env, av, p);
	close(p->fd[0]);
	close(p->fd[1]);
	while (wait(NULL) != -1)
		;
	free(p);
}
