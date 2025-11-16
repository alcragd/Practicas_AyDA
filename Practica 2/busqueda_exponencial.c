#include <stdio.h>
#include <stdlib.h>

int expSearch(int *A,int n,int v);
int binarySearch(int *A,int l,int r,int v);

int main(int argc,char **argv){
    if(argc!=2)
        exit(1);

    int n, *A, res, val;
    n=atoi(argv[1]);
    A=malloc(n*sizeof(int)); //Que hace este malloc????? 🤔

    scanf("%d",&val);

    for(int i=0;i<n;++i)
        scanf("%d",&A[i]);

    res=expSearch(A,n,val);

    printf("\n%d",res);

    free(A);
    
    return 0;
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

int expSearch(int *A,int n,int v){
    int i=1;
    
    while(i-1<n){
        if(A[i-1]==v)
            return i-1; 
        if(A[i-1]>v) 
            break;
        i<<=1;
    }
    return binarySearch(A, (i>>1)-1, i-1>n-1 ? n-1 : i-1, v);
}
