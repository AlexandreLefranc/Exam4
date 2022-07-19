#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

enum type
{
	NONE,
	PIPE,
	BREAK,
	END
};

enum pipe
{
	READ = 0,
	WRITE = 1
};

static void	print_tab(char **tab)
{
	for (int i = 0; tab[i] != NULL; i++)
		dprintf(2, "[%s] ", tab[i]);
	dprintf(2, "\n");
}

static int	get_type(char *str)
{
	if (str == NULL)
		return (END);
	if (strcmp(str, "|") == 0)
		return (PIPE);
	if (strcmp(str, ";") == 0)
		return (BREAK);
	return (NONE);
}

static int	get_cmd_len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
		i++;
	return (i);
}
static int	execute(int argc, char **argv, char **cmd, char **envp)
{
	int	pos;	// Start of command
	int	i;	// length of command
	int	ntype;	// next type
	int	ptype;	// prev type
	int	pipefd[2];
	int	savefd;
	pid_t	pid;

	argv++;
	pos = 0;
	while (pos < argc - 1)
	{
		dprintf(2, "-----------------------------------------\n");
		print_tab(argv + pos);
		print_tab(cmd + pos);
		i = get_cmd_len(cmd + pos);
		dprintf(2, "i=%d\n", i);
		if (strcmp(argv[pos], "cd") == 0)
		{
			dprintf(2, "Run cd\n");
			if (i != 2)
				write(2, "error arg\n", 10);
			else if (chdir(cmd[pos + 1]) < 0)
				write(2, "cd failed\n", 10);
		}
		else if (i > 0)
		{
			dprintf(2, "Run command\n");
			ptype = get_type(argv[pos - 1]);
			ntype = get_type(argv[pos + i]);
			dprintf(2, "ptype=%d || ntype=%d\n", ptype, ntype);
			if (ntype == PIPE)
				pipe(pipefd);
			pid = fork();
			if (pid == 0)
			{
				if (ptype == PIPE)
					dup2(savefd, 0);
				if (ntype == PIPE)
					dup2(pipefd[WRITE], 1);
				execve(cmd[pos], cmd + pos, envp);
				write(2, "execve failed\n", 14);
				free(cmd);
				exit(1);
			}
			else
			{
				if (ptype == PIPE)
					close(savefd);
				if (ntype == PIPE)
				{
					close(pipefd[WRITE]);
					savefd = pipefd[READ];
				}
				waitpid(pid, NULL, 0);
			}
		}
		pos = pos + i + 1;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd;
	int	i;

	if (argc == 1)
		return (0);
	cmd = malloc(sizeof(*cmd) * argc);
	i = 1;
	while (argv[i] != NULL)
	{
		if (get_type(argv[i]) != NONE)
			cmd[i - 1] = NULL;
		else
			cmd[i - 1] = argv[i];
		i++;
	}
	cmd[i - 1] = NULL;
	execute(argc, argv, cmd, envp);
	free(cmd);
	return (0);
}
