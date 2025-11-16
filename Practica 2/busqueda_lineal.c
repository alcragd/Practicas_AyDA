#include <stdio.h>
#include <stdlib.h>

int linearSearch(int *A,int n,int v);

int main(int argc,char **argv){
    if(argc!=2)
        exit(1);

    int n, *A, res, val;
    n=atoi(argv[1]);
    A=malloc(n*sizeof(int));

    scanf("%d",&val);

    for(int i=0;i<n;++i)
        scanf("%d",&A[i]);

    res=linearSearch(A,n,val);

    printf("\n%d",res);


    return 0;
}


int linearSearch(int *A,int n,int v){
    for(int i=0;i<n;++i)
        if(A[i]==v)
            return i;
    return -1;
}

