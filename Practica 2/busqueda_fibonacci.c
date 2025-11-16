#include <stdio.h>
#include <stdlib.h>

int fiboSearch(int *A,int n,int v);
int binarySearch(int *A,int l,int r,int v);

int main(int argc,char **argv){
    if(argc!=2)
        exit(1);

    int n, *A, res, val;
    n=atoi(argv[1]);
    A=malloc(n*sizeof(int));

    scanf("%d",&val);

    for(int i=0;i<n;++i)
        scanf("%d",&A[i]);

    res=fiboSearch(A,n,val);

    printf("\n%d",res);

    free(A);

    return 0;
}

int fiboSearch(int *A,int n,int v){
    int a = 0, b = 1, c = 1, i;

    while(c - 1 < n){
        if(A[c-1]==v)
            return c-1; 
        if(A[c-1]>v) 
            break;
        a = b;
        b = c;
        c = a+b;
    }
    return binarySearch(A, b-1, c-1>n-1 ? n-1 : c-1, v);
}

int binarySearch(int *A,int l,int r,int v){
    int m;
    while(l<=r){
        m=(r+l)/2;
        if(A[m]==v)
         return m;
        
        A[m] > v ? (r = m - 1) : (l = m + 1);
    }
    return -1;
}