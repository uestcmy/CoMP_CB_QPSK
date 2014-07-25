#include <stdio.h>
#include <stdlib.h>
#include "chol_inv_4.cpp"
#define N 100

int main(){
    freopen("multin.txt","r",stdin); 
    freopen("multout.txt","w",stdout); 
    
    int m;
    int n;
    int p; 
    COMPLEX a[N][N];
    COMPLEX b[N][N];
    COMPLEX c[N][N];
    scanf("%d%d%d",&m,&n,&p);

    for( int i = 0 ; i < m ; i++){
        for( int j = 0 ; j < n ; j++){
            scanf("%lf",&a[i][j].re);
        }
    }    


    for( int i = 0 ; i < m ; i++){
        for( int j = 0 ; j < n ; j++){
            scanf("%lf",&a[i][j].im);
        }
    }    

    for( int i = 0 ; i < n ; i++){
        for( int j = 0 ; j < p ; j++){
            scanf("%lf",&b[i][j].re);
        }
    }    

    for( int i = 0 ; i < n ; i++){
        for( int j = 0 ; j < p ; j++){
            scanf("%lf",&b[i][j].im);
        }
    }

/*
    for( int i = 0 ; i < m ; i++ ){
        for( int j = 0 ; j < n ; j++ ){
           printf("%lf   ",a[i][j].re);

        }
        printf("\n");
    }   

*/    
    CMatMult(&a[0][0],&b[0][0],&c[0][0],3,2,1);

    for( int i = 0 ; i < m ; i++ ){
        for( int j = 0 ; j < p ; j++ ){
           printf("%lf   ",c[i][j].im);

        }
        printf("\n");
    }   

    
    return 0;

}
