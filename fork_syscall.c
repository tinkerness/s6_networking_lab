#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    if (fork() == 0) {
        printf("Child has pid = %d\n", getpid());
        printf("parent of child has pid = %d\n", getppid());
    }
    else {
        printf("parent has pid = %d\n", getpid());
    }
}