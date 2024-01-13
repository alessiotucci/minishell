#include <stdio.h>
#include <string.h>
/*
char	*extract_content(const char* str)
{
	char*	start_quote;
	char*	end_quote;

	start_quote = strchr(str, '\"');
	if (start_quote)
	{
		end_quote = strchr(start_quote + 1, '\"');
		if (end_quote)
		{
			char content[end_quote - start_quote];
			strncpy(content, start_quote + 1, end_quote - start_quote - 1);
			content[end_quote - start_quote - 1] = '\0';
			printf("%s\n", content);
			return (content);
		}
	}
}

int	main()
{
	extract_content("\"$HOME\"");  // prints $HOME
	extract_content("\"  .  ciao  .  \"");  // prints ciao
	return 0;
}
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* extract_content(const char* str)
{
	char*	start_quote;
	char*	end_quote;
	char*	content;
	start_quote = strchr(str, '\"');
	if (start_quote)
	{
		end_quote = strchr(start_quote + 1, '\"');
		if (end_quote)
		{
			content = malloc(end_quote - start_quote);
			if(content == NULL)
				return (perror("Error: malloc"), NULL);
			strncpy(content, start_quote + 1, end_quote - start_quote - 1);
			content[end_quote - start_quote - 1] = '\0';
			return (content);
		}
	}
	return (NULL);
}

int main()
{
	char* result;

	result = extract_content("\"$HOME\"");  // prints $HOME
	if(result != NULL)
	{
		printf("%s\n", result);
		free(result);
	}
	result = extract_content("\"  .  ciao  .  \"");  // prints ciao
	if(result != NULL)
	{
		printf("%s\n", result);
		free(result);
	}
	return 0;
}

