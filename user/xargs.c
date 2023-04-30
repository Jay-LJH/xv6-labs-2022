#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#define BUFSIZ 20
int main(int argc, char *argv[]){
    if(argc<2){
        printf("need arguments\n");
        exit(1);
    }
    char *param[MAXARG],buf[MAXARG][BUFSIZ],*p=buf[0],*p2=buf[0];
    int cnt=argc-1;
    for(int i=1;i<argc;i++){
       param[i-1]=argv[i];
    }
    while(read(0,p2,1)){
        if(*p2=='\n'){
            *p2='\0';
            param[cnt]=p;
            cnt++;
            p+=BUFSIZ;
            p2=p;
        }
        else{
            p2++;
        }
    }
    if(!fork()){
        exec(argv[1],param);
    }
    else{
        wait(0);
    }
    return 0;
}