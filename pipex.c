/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:16:00 by walker            #+#    #+#             */
/*   Updated: 2021/09/16 17:40:07 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double_ptr(char **str)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	execve_for_path(char **cmd, char **env)
{
	char	*path;
	char	**paths;
	char	*tmp;
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = (env[i] + 5);
		}
		i++;
	}
	paths = ft_split(path, ':');
	while (paths[i])
	{
		if (cmd[0][0] != '/')
		{
			tmp = ft_strjoin(paths[i], "/");
			tmp = ft_stradd(tmp, cmd[0]);
		}
		execve(tmp, cmd, env);
		i++;
	}
	free_double_ptr(paths);
}

void	parent_process(int out, int child, char **argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv[3], ' ');
	dup2(child, STDIN_FILENO);
	close(child);
	dup2(out, STDOUT_FILENO);
	execve_for_path(cmd, env);
	free_double_ptr(cmd);
	return ;
}

void	child_process(int in, int parent, char **argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv[2], ' ');
	dup2(parent, STDOUT_FILENO);
	close(parent);
	dup2(in, STDIN_FILENO);
	execve_for_path(cmd, env);
	free_double_ptr(cmd);
	return ;
}

void	pipex(int in, int out, char **argv, char **env)
{
	int		pip[2];
	pid_t	parent;

	pipe(pip);
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	if (parent == 0)
	{
		close(pip[0]);
		child_process(in, pip[1], argv, env);
	}
	else
	{
		close(pip[1]);
		waitpid(parent, NULL, 0);
		parent_process(out, pip[0], argv, env);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int		fd1;
	int		fd2;

	if (argc != 5)
	{
		printf("Usage : file1 cmd1 cmd2 file2\n");
		exit(-1);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	pipex(fd1, fd2, argv, env);
	return (1);
}
