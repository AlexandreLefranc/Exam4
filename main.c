#include "microshell.h"

int	main(int argc, char **argv, char **envp)
{
	char *str = ft_strdup("Coucou ;D");

	printf("%s\n", str);
	free(str);
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
