#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc!=2){
        write(1,"wrong args num\n",strlen("wrong args num\n"));
        exit(0);
    }
    int i=atoi(argv[1]);
    if(sleep(i)!=0){
        write(1,"sleep fail\n",strlen("sleep fail\n"));
    }
    exit(0);
}
