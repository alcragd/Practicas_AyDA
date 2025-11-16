#include <stdio.h>
#include <stdlib.h>
#include "abb/abb.h"

#include "tiempo/tiempo.h"



int main(int argc,char **argv){
    if(argc!=2)
        exit(1);

    int n, res, val;
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
    abb tree;
    Initialize_ABB(&tree);
    
    n=atoi(argv[1]);

    scanf("%d",&val);

    for(int i=0;i<n;++i) {
        int num;
        scanf("%d",&num);
        Insert_ABB(&tree,num);
    }

    uswtime(&utime0, &stime0, &wtime0);
    res=abbSearch(&tree,val);
    uswtime(&utime1, &stime1, &wtime1);

    printf("\n%d",res);
    printf("\n%.10e",wtime1 - wtime0);

    Destroy_ABB(&tree);
    
    return 0;
}

