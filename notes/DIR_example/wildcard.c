#include <stdio.h>
#include "../../libft/libft.h"
#include "../../minishell.h"
size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*my_strchr(char *str, int cherry)
{
	size_t	count;

	count = 0;
	while (str[count])
	{
		if (str[count] == (char)cherry)
			return (&str[count]);
		count++;
	}
	return (null);
}

int	my_strcmp(const char *str1, const char *str2)
{
	size_t	count;

	count = 0;
	while (str1[count] != '\0' || str2[count] != '\0')
	{
		if (str1[count] > str2[count])
			return (1);
		else if (str1[count] < str2[count])
			return (-1);
		count++;
	}
	return (0);
}

static int	find_matches(char *wildcard, char *name)
{
	char	*prefix;
	char	*suffix;
	char	*asterix;
	char	*copy;

	copy = ft_strdup(wildcard);
	if (copy[0] == '*')
	{
		prefix = null;
		suffix = &copy[1];
	}
	else
	{
		asterix = my_strchr(copy, '*');
		if (asterix != null)
		{
			*asterix = '\0';
			prefix = copy;
			suffix = asterix + 1;
		}
		else
		{
			// handle the case where there is no '*' in the wildcard
			// for example, you could set prefix and suffix to null
			prefix = copy;
			suffix = "";
		}
	}
	if (prefix != null && ft_strncmp(name, prefix, ft_strlen(prefix)) != 0)
		return (free(copy),1);
	if (suffix != null && my_strcmp(name + ft_strlen(name) - ft_strlen(suffix), suffix) != 0)
		return (free(copy),1);
	return (free(copy),0);
}
// your functions here

int main(int ac, char *av[])
{
	char *wildcard = av[1];
	char *name = av[2];
	(void)av;
	if (ac == 3)
	{
		printf("FIND_MATCHES\nMatch result of wildcard '%s' and name '%s'\n. . .\n", wildcard, name);
		int match_result = find_matches(wildcard, name);
		if (match_result == 0)
			printf("%s0 means success%s\n", GREEN, RESET);
		else
			printf("%s1 means failure, no matches%s\n", RED, RESET);
		int result = find_matches(wildcard, name);
		printf("after the first function call result of wildcard '%s' and name '%s'is\n [%d]!\n", wildcard, name, result);
	}
	else
		printf("USAGE: ./a.out \"wildcard\", name\n");
	return 0;
}

