#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define BUFSIZ 10
int main(int argc, char *argv[])
{
    int fd[2],fd2[2];
    if (pipe(fd) == -1) {
        printf("pipe error");
        exit(1);
    }
    if (pipe(fd2) == -1) {
        printf("pipe error");
        exit(1);
    }
    if(fork()!=0){
        char buf[BUFSIZ];
        close(fd[0]);
        close(fd2[1]);
        write(fd[1],"ping",strlen("ping"));
        read(fd2[0],buf,BUFSIZ);
        printf("%d: received %s\n",getpid(),buf);
    }
    else{
        char buf[BUFSIZ];
        close(fd[1]);
        close(fd2[0]);
        read(fd[0],buf,BUFSIZ);
        printf("%d: received %s\n",getpid(),buf);
        write(fd2[1],"pong",strlen("pong"));
    }
    exit(0);
}
