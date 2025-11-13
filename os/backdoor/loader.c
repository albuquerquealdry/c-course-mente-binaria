/*

 * loader.c - PoC de "Loader"

 * Executa um payload separado (./payload) usando fork/execve.

 * Este é um ambiente de laboratório controlado.

 */



#include <stdio.h>

#include <unistd.h>     // Para fork(), execve(), getpid()

#include <sys/wait.h>   // Para waitpid()

#include <stdlib.h>     // Para exit()



int main(int argc, char *argv[]) {

    

    pid_t pid;

    int status;



    /* * Preparação: Definir o payload a ser executado.

     * Note: "./payload" significa "o arquivo 'payload' no diretório atual".

     */

    char *args[] = {"./payload", NULL}; 

    char *envp[] = {NULL}; // Usar ambiente padrão



    printf("--- [Pai-Loader, PID: %d] Iniciando.\n", getpid());

    printf("--- [Pai-Loader, PID: %d] Objetivo: carregar e executar './payload'.\n", getpid());



    // 1. CRIAÇÃO (A chamada fork())

    pid = fork(); 



    if (pid < 0) {

        /* Erro Fatal */

        perror("fork falhou");

        exit(1);

    }

    else if (pid == 0) {

        /* == 0: Estamos no Processo Filho */

        

        printf("   [Filho-Loader, PID: %d] Fork bem-sucedido. Executando o payload via execve()...\n", getpid());

        

        // 2. SUBSTITUIÇÃO (A chamada execve())

        // O Filho se transforma no nosso payload.

        execve(args[0], args, envp);

        

        /* Se chegamos aqui, o execve() falhou */

        perror("   [Filho-Loader] ERRO: execve falhou");

        printf("   [Filho-Loader] Certifique-se que o './payload' foi compilado e está no mesmo diretório.\n");

        exit(2);

    }

    else {

        /* > 0: Estamos no Processo Pai */

        

        printf("--- [Pai-Loader, PID: %d] Criei o filho com PID: %d.\n", getpid(), pid);

        printf("--- [Pai-Loader, PID: %d] Esperando o payload (filho) terminar...\n", getpid());



        // 3. TÉRMINO (A chamada waitpid())

        waitpid(pid, &status, 0); 

        

        printf("--- [Pai-Loader, PID: %d] O payload (filho) terminou. Encerrando.\n", getpid());

    }



    return 0;

}
