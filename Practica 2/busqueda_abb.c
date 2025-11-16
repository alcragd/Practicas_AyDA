#include <stdio.h>
#include <stdlib.h>
#include "abb/abb.h"




int main(int argc,char **argv){
    if(argc!=2)
        exit(1);

    int n, res, val;
    abb tree;
    Initialize_ABB(&tree);

    
    n=atoi(argv[1]);
    

    scanf("%d",&val);

    for(int i=0;i<n;++i) {
        int num;
        scanf("%d",&num);
        Insert_ABB(&tree,num);
    }

    res=abbSearch(&tree,val);

    printf("\n%d",res);

    Destroy_ABB(&tree);
    
    return 0;
}

