#include <stdio.h>
#include "../../libft/libft.h"

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
	return (NULL);
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
	if (wildcard[0] == '*')
	{
		prefix = NULL;
		suffix = &wildcard[1];
	}
	/*else if (wildcard[ft_strlen(wildcard) - 1] == '*')
	{
		suffix = NULL;
		wildcard[ft_strlen(wildcard) -1] = '\0';
		prefix = wildcard;
	}*/
	else
	{
		asterix = my_strchr(wildcard, '*');
		if (asterix != NULL)
		{
			*asterix = '\0';
			prefix = wildcard;
			suffix = asterix + 1;
		}
		else
		{
			// Handle the case where there is no '*' in the wildcard
			// For example, you could set prefix and suffix to NULL
			prefix = wildcard;
			suffix = "";
		}
	}
//	printf("prefix:%s, suffix:%s\n", prefix, suffix);
	if (prefix != NULL && ft_strncmp(name, prefix, ft_strlen(prefix)) != 0)
//		return (printf("My dear, comparing: %s, with %s)", name, prefix));
		return (1);
	if (suffix != NULL && my_strcmp(name + ft_strlen(name) - ft_strlen(suffix), suffix) != 0)
//		return (printf("the comparison between %s and [%s]\n", name + ft_strlen(name) - ft_strlen(suffix), suffix));
		return (1);
	return (0);
}
// your functions here

int main(int ac, char *av[])
{
	char *wildcard = av[1];
	char *name = av[2];
	printf("0 means success\n 1 means failure, no matches\n");
	(void)av;
	if (ac == 3)
	{
		int match_result = find_matches(wildcard, name);
		printf("FIND_MATCHES\nMatch result of wildcard '%s' and name '%s'\n%d\n", wildcard, name, match_result);
	}
	else
		printf("USAGE: ./a.out \"wildcard\", name\n");
	return 0;
}

