#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>    // Inclusione per isdigit
#include <string.h>   // Inclusione per strlen

static bool is_valid_exit_arg(char *args[]) {
    int i, j;

    i = 0;
    while (args && args[i]) {
        j = 0;
        while (args[i][j]) {
            if (args[i][j] == '-' || args[i][j] == '+')  // Aggiunto il controllo per i segni
                j++;
            if (!isdigit(args[i][j]))
                return false;
            j++;
        }
        i++;
    }
    return true;
}

int main(int argc, char *argv[]) {
    long exit_code;

    if (argc > 1) {
        if (!is_valid_exit_arg(argv + 1) || strlen(argv[1]) > 19) {
            fprintf(stderr, "exit: not a valid argument\n");
            exit_code = 255;
        } else {
            exit_code = atol(argv[1]);
        }
    } else {
        exit_code = 0;  // Default exit code if no argument is provided
    }

    fprintf(stderr, "exit\n");
    exit((int)exit_code);
}

