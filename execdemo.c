#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("hii... this is the beginning of execdemo.c\n");
    printf("going to call exec.c using the system call execv()\n");

    char *args[] = {"./exec", NULL};
    execv(args[0], args);

    // This code will not be executed
    printf("execdemo.c ends here\n");
}