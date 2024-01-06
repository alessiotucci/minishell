#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exit_builtin() {
    printf("Exiting Minishell...\n");
    exit(0);
}

int main() {
    char command[100];

    while (1) {
        printf("Minishell> ");
        fgets(command, sizeof(command), stdin);

        // Rimuovi il carattere newline dalla fine dell'input
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        if (strcmp(command, "exit") == 0) {
            exit_builtin();
        } else {
            // Altri controlli per altri comandi built-in o esecuzione di processi esterni
            // ...
            printf("Comando sconosciuto: %s\n", command);
        }
    }

    return 0;
}
