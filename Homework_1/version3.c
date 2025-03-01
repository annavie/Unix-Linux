#include <stdio.h>
#include <unistd.h>

int main() {
  
    execl("./triangle", "triangle", NULL);
    printf("Exec failed for triangle!\n");  
    return 1;

    execl("./rectangle", "rectangle", NULL);
    printf("Exec failed for rectangle!\n");  //  NEVER run
    return 1;
}
