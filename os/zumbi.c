#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

// @puka6doll the project is for analize the beheivor when the process son not die 

int main() {

    pid_t pid;
    // Cria o processo filho
    pid = fork();
    if (pid > 0) {

        // --- Código do PAI ---

        printf("PAI: Criei um filho com PID: %d\n", pid);

        printf("PAI: Agora vou dormir por 60 segundos, sem esperar o filho.\n");

        sleep(60); // O pai "irresponsável" dorme

        printf("PAI: Acordei e terminei.\n");

    } else if (pid == 0) {

        // --- Código do FILHO ---

        printf("FILHO: Eu sou o filho. Vou terminar agora.\n");

        exit(0); // O filho termina imediatamente

    } else {

        // --- Erro ---

        perror("Erro no fork");

        return 1;
    }
    return 0;
}
