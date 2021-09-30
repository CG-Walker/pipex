/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:16:00 by walker            #+#    #+#             */
/*   Updated: 2021/09/30 15:12:11 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execve_for_path(char **cmd, char **env)
{
	char	*path;
	char	**paths;
	char	*tmp;
	size_t	i;

	i = -1;
	tmp = NULL;
	path = get_path(env);
	if (!path)
		return ;
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		if (cmd[0][0] != '/')
		{
			tmp = ft_strjoin(paths[i], "/");
			tmp = ft_stradd(tmp, cmd[0]);
		}
		execve(tmp, cmd, env);
		free(tmp);
		tmp = NULL;
	}
	free(tmp);
	free_double_ptr(paths);
	write(2, "pipex: command not found\n", 25);
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
	pid_t	id;
	pid_t	id_2;

	pipe(pip);
	id = fork();
	if (id < 0)
		return (perror("pipex"));
	if (id == 0)
	{
		close(pip[0]);
		child_process(in, pip[1], argv, env);
	}
	else
	{
		id_2 = fork();
		if (id_2 < 0)
			return (perror("pipex"));
		if (id_2 == 0)
		{
			close(pip[1]);
			waitpid(id, NULL, 0);
			parent_process(out, pip[0], argv, env);
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int		fd1;
	int		fd2;

	if (argc != 5 || !ft_strlen(argv[2]) || !ft_strlen(argv[3]))
	{
		usage();
		exit(-1);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("pipex");
		return (-2);
	}
	pipex(fd1, fd2, argv, env);
	return (0);
}
