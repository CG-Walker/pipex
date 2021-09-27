/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:16:41 by walker            #+#    #+#             */
/*   Updated: 2021/09/27 18:51:20 by cgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

# include "libft/libft.h"

void	pipex(int in, int out, char **argv, char **env);
void	child_process(int in, int parent, char **argv, char **env);
void	parent_process(int out, int child, char **argv, char **env);
void	execve_for_path(char **cmd, char **env);
char	*get_path(char **env);
void	free_double_ptr(char **str);
void	usage(void);

#endif