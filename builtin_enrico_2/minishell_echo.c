#include <stdio.h>
#include <string.h>

void minishell_echo(char *args[]) {
    int i = 1;
    int suppress_newline = 0;

    // Check for the -n option
    if (args[1] != NULL && strcmp(args[1], "-n") == 0) {
        suppress_newline = 1;
        i++;
    }

    while (args[i] != NULL) {
        printf("%s", args[i]);

        // Print space between arguments
        if (args[i + 1] != NULL) {
            printf(" ");
        }

        i++;
    }

    // Print newline unless -n option is used
    if (!suppress_newline) {
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    // Pass command-line arguments to minishell_echo
    minishell_echo(argv);

    return 0;
}

