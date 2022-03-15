/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaoufi <aelaoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:45:50 by aelaoufi          #+#    #+#             */
/*   Updated: 2022/03/15 18:40:59 by aelaoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env ,"PATH=", 5))
			return (*env + 5);
		env++;
	}
	return (0);
}

void exec_path(char **env, char *cmd)
{
	char	*patt;
	char	**paths;
	char	**cmds;
	int		i;
	
	i = 0;
	patt = find_path(env);
	paths = ft_split(patt, ':');
	cmds = ft_split(cmd, ' ');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmds[0]);
		//printf("%s\n",paths[i]);
		if (access(paths[i], X_OK) == 0)
			execve(paths[i], cmds, env);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int pid1;
	int fd[2];
	int inputfile;
	int outputfile;
	
	if (ac != 5)
	{
		perror("Wrong number or arguments");
		return (0);
	}
	
	inputfile = open(av[1], O_RDONLY);
	outputfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	(void)ac;
	if  (pipe(fd) == -1)
		return 1;
	pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		//child process 1 
		dup2(fd[1], STDOUT_FILENO);
		dup2(inputfile, STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_path(env, av[2]);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return 3;
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(outputfile, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_path(env, av[3]);
	}
	waitpid(pid1, NULL, 0);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
}