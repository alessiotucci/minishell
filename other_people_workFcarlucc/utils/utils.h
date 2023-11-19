#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>

size_t	ft_strlen(const char *s);
int     ft_isspace(char c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isalpha(int c);
int		free_matrix(char **s);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);

#endif