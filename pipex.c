/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:46:30 by sdemaude          #+#    #+#             */
/*   Updated: 2024/02/18 13:03:43 by sdemaude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void static	cmd1(int *fds, int *pipe_fd, char *cmd, char **envp)
{
	char	*path;
	char	**tab_cmd;

	tab_cmd = ft_split(cmd, ' ');
	if (*tab_cmd)
	{
		close(fds[1]);
		close(pipe_fd[0]);
		dup2(fds[0], 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		path = get_valid_path(tab_cmd[0], envp);
		if (path)
			execve(path, tab_cmd, envp);
		free(path);
	}
	free_tab(tab_cmd);
	perror("First command not found");
	exit(127);
}

void static	cmd2(int *fds, int *pipe_fd, char *cmd, char **envp)
{
	char	*path;
	char	**tab_cmd;

	tab_cmd = ft_split(cmd, ' ');
	if (*tab_cmd)
	{
		close(fds[0]);
		close(pipe_fd[1]);
		dup2(fds[1], 1);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		path = get_valid_path(tab_cmd[0], envp);
		if (path)
			execve(path, tab_cmd, envp);
		free(path);
	}
	free_tab(tab_cmd);
	perror("Second command not found");
	exit(127);
}

int	static	failed_fork(void)
{
	perror("Failed to fork");
	exit(EXIT_FAILURE);
}

int static	pipex(int *fds, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid[2];

	pipe(pipe_fd);
	pid[0] = fork();
	if (pid[0] == 0)
		cmd1(fds, pipe_fd, argv[2], envp);
	else if (pid[0] < 0)
		failed_fork();
	pid[1] = fork();
	if (pid[1] == 0)
		cmd2(fds, pipe_fd, argv[3], envp);
	else if (pid[1] < 0)
		failed_fork();
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], &status, 0);
		return (WEXITSTATUS(status));
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int	fds[2];
	int	exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("Incorrect number of arguments !\n", STDERR_FILENO);
		return (1);
	}
	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] < 0)
	{
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fds[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds[1] < 0)
	{
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit_status = pipex(fds, argv, envp);
	close(fds[0]);
	close(fds[1]);
	return (exit_status);
}
