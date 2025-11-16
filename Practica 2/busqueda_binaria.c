#include <stdio.h>
#include <stdlib.h>

int expSearch(int *A,int n,int v);
int binarySearch(int *A,int n,int v);

int main(int argc,char **argv){
    if(argc!=2)
        exit(1);

    int n, *A, res, val;
    n=atoi(argv[1]);
    A=malloc(n*sizeof(int));

    scanf("%d",&val);

    for(int i=0;i<n;++i)
        scanf("%d",&A[i]);

    res=expSearch(A,n,val);

    printf("\n%d",res);

    return 0;
}

int binarySearch(int *A,int n,int v){
    int l,r,m;
    l=0; r=n-1;

    while(l<=r){
        m=(r+l)/2;
        if(A[m]==v)
         return m;
        
        A[m] < v ? (r = m - 1) : (l = m + 1);
    }
}