#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid1 == 0) {
        execl("./triangle", "triangle", NULL);
        printf("Exec failed for triangle!\n");  
        return 1;
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        printf("Fork failed!\n");
        return 1;
    } else if (pid2 == 0) {
        execl("./rectangle", "rectangle", NULL);
        printf("Exec failed for rectangle!\n"); 
        return 1;
    }

    wait(NULL);
    wait(NULL);

    printf("Both child processes finished.\n");
    return 0;
}
