#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    fork();
    fork();
    printf("hello world from PID %d!\n", (int) getpid());
    return 0;
}