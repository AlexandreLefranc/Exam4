#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define STDIN 0
#define STDOUT 1
#define PIPE 2
#define BREAK 3
#define END 4

int ftype(char *arg)
{
	if (!arg)
		return (END);
	if (!strcmp(arg, ";"))
		return (BREAK);
	if (!strcmp(arg, "|"))
		return (PIPE);
	return (0);
}

int print(char **all, char *str, char *cmd, int type)
{
	int i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	i = 0;
	while (cmd[i])
		write(2, &cmd[i++], 1);
	write(2, "\n", 1);
	if (type)
	{
		free(all);
		exit(1);
	}
	return (1);
}

int execute(char **cmds, int argc, char **argv, char **env)
{
	int i = 0;
	int pos = 0;
	int type;

	int pfd[2];
	int ofd[2];
	pid_t pid;
	int ret;
	int status;

	while (pos < argc)
	{
		i = 0;
		while (cmds[pos + i])
			i++;
		if (!strcmp(cmds[pos], "cd"))
		{
			if (i != 2)
				print(cmds, "error: cd: bad arguments\n", NULL, 0);
			else if ((chdir(cmds[pos + 1]) < 0))
				print(cmds, "error: cd: cannot change directory to ", cmds[pos + 1], 0);
		}
		else
		{
			if ((type = ftype(argv[pos + i + 1])))
			{
				if (type == PIPE && pipe(pfd) < 0)
					print(cmds, "error: fatal", NULL, 1);
				if ((pid = fork()) < 0)
					print(cmds, "error: fatal", NULL, 1);
				if (pid == 0)
				{
					if (type == PIPE && dup2(pfd[1], STDOUT) < 0)
						print(cmds, "error: fatal", NULL, 1);
					if (ftype(argv[pos]) == PIPE && dup2(ofd[0], STDIN) < 0)
						print(cmds, "error: fatal", NULL, 1);
					ret = execve(cmds[pos], &cmds[pos], env);
					if (ret < 0)
						print(cmds, "error: cannot execute ", cmds[pos], 0);
					exit(ret);
				}
				else
				{
					waitpid(pid, &status, 0);
					if (type == PIPE || ftype(argv[pos]) == PIPE)
					{
						close(pfd[1]);
						if (type == END || type == BREAK)
							close(ofd[0]);
					}
					if (argv[pos] && ftype(argv[pos]) == PIPE)
						close(ofd[0]);
					if (WIFEXITED(status))
						ret = WEXITSTATUS(status);
				}
			}
			ofd[0] = pfd[0];
			ofd[1] = pfd[1];
		}
		pos += i + 1;
	}
	return (ret);
}

int main(int argc, char **argv, char **env)
{
	if (argc == 1)
		return (0);
	char **cmds = malloc(sizeof(char *) * argc);
	for (int i = 1; i <= argc; i++)
	{
		cmds[i - 1] = argv[i];
		if (argv[i] && strcmp(argv[i], ";") == 0)
			cmds[i - 1] = NULL;
		if (argv[i] && strcmp(argv[i], "|") == 0)
			cmds[i - 1] = NULL;
	}
	execute(cmds, argc, argv, env);
	free(cmds);
	return (0);
}
