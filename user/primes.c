#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    int fd[2], right[2];
    if (pipe(fd) == -1)
    {
        printf("pipe error\n");
        exit(1);
    }
    if (pipe(right) == -1)
    {
        printf("pipe error\n");
        exit(1);
    }
    if (fork() != 0)
    {
        close(right[0]);
        close(fd[1]);
        for (int i = 2; i < 35; i++)
        {
            write(right[1], &i, 4);
        }
        close(right[1]);
        int p;
        while (read(fd[0], &p, 4))
        {
            printf("prime %d\n", p);
        }
    }
    else
    {
        close(fd[0]);
        close(right[1]);
        int n;
        while (read(right[0], &n, 4))
        {
            write(fd[1], &n, 4);
            int left = dup(right[0]);
            close(right[0]);
            if (pipe(right) == -1)
            {
                printf("pipe error\n");
                exit(1);
            }
            if (fork() != 0)
            {
                close(right[0]);
                int p;
                while (read(left, &p, 4))
                {
                    if (p % n)
                    {
                        write(right[1], &p, 4);
                    }
                }
                close(fd[1]);
                close(right[1]);
                close(left);
                exit(0);
            }
            close(right[1]);
            close(left);
        }
        close(fd[1]);
    }
    exit(0);
}
