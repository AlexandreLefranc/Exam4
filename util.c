#include "microshell.h"

void	*ft_calloc(size_t	size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(char *)(ptr+i) = 0;
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	dup = ft_calloc(len + 1);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}
