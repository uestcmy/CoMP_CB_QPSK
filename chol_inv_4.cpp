#include <stdio.h>
#include <math.h>
#define N 100
/*[H_i_re H_i_im]=chol_inv_4(real(H),imag(H));
这是一个基于改进型cholesky原理的矩阵求逆函数,只能分析正定hermite矩阵H;
real(H),imag(H)：分别为输入求逆矩阵的实部和虚部；
H_i_re，H_i_im：分别为输出逆矩阵的实部和虚部；
改进型cholesky原理：matrix=LDL',"'"表示共轭转置,matrix_i=L_i'*D_i*L_i;

 作者: lyf
 电子科技大学 通信与信息工程学院 
 School of Communication and Information Engineering, 
 University of Electronic Science and Technology of China, Chengdu, Sichuan, China
 Email: 764778793@qq.com
 2013-12-12
*/
typedef struct comp {
    double re;
    double im;
}COMPLEX;
void cdev(COMPLEX *x,COMPLEX *y,COMPLEX *res);
void cmult(COMPLEX *x,COMPLEX *y,COMPLEX *res){
    double a,b;
    //printf("\nin cmult\n");
    //printf("%lf %lf %lf %lf\n",x->re,x->im,y->re,y->im );
    a = x->re * y->re - x->im * y -> im;
    b = x->re * y->im + x->im * y -> re;
    res->re = a;
    res->im = b;
}
void cadd(COMPLEX *x,COMPLEX *y,COMPLEX *res){
    res->re = x->re + y->re;
    res->im = x->im + y->im;
}
void mult(double x_re,double x_im,double y_re,double y_im,double *p1,double *p2)
{
	double a,b;
	a=x_re*y_re-x_im*y_im;
	b=x_re*y_im+x_im*y_re;
	*p1=a;
	*p2=b;
}

 void cinv22(COMPLEX *a,COMPLEX *b){
     double tmp = 1/(a->re*(a+3)->im - (a+1)->im*(a+2)->re);

     COMPLEX res1,res2,res3,res4,one;
     cmult((a),(a+3),&res1);
     cmult((a+1),(a+2),&res2);
     res2.re *= -1;
     res2.im *= -1;
     cadd(&res1,&res2,&res3);

      one.re = 1;
      one.im = 0;
      cdev(&one,&res3,&res4);

      cmult(&res4,a+3,b);
      cmult(&res4,a+1,b+1);
      (b+1)->re *= -1;
      (b+1)->im *= -1;

      cmult(&res4,a+2,b+2);
      (b+2)->re *= -1;
      (b+2)->im *= -1;

      cmult(&res4,a,b+3);


 }

void cdev(COMPLEX *x,COMPLEX *y,COMPLEX *res){
    double a,b;
    a = x->re * y->re + x->im * y -> im;
    a /= (y->re*y->re + y->im*y->im);
    b = x->im * y->re - x->re * y->im;
    b /= (y->re*y->re + y->im*y->im);
    res->re = a;
    res->im = b;
}
double soc(double x_re,double x_im)
{
	double z;
	z=x_re*x_re+x_im*x_im;
	return(z);
}

void CMatMult(COMPLEX *p1,COMPLEX *p2,COMPLEX *p3,int m,int n,int p){//all the matrix in the multiplex must be allot the memory space
    int i,j,k;
    COMPLEX sum;
    //printf("in cmatmult\n");
    for( i = 0 ; i < m ; i++ ){
        for( j = 0 ; j < p ; j++ ){
            sum.re = 0;
            sum.im = 0;
            for( k = 0 ; k < n ; k++ ){
                //printf("ijk:%d %d %d",i,j,k);
                COMPLEX tmp;
                COMPLEX ori = sum;
                cmult((p1+i*n+k),(p2+k*p+j),&tmp);
                cadd(&ori,&tmp,&sum);
            }
            *(p3+i*p+j)= sum;  //sprintf(str,"\n%d %d %d %d sum : %lf \n",m,n,i,j,sum.re);qDebug() << str;
        }
    } 
    
}
void Matrix_mult441(double a1_re[][4],double a1_im[][4],double b1_re[][1],double b1_im[][1],double c1_re[][1],double c1_im[][1])
{
    int i,j,k;
    double sum_re,sum_im;
    double temp_re,temp_im;
    double *p_re;
    double *p_im;
    p_re=&temp_re;
    p_im=&temp_im;
    for(i=0;i<4;i++)
    {
        for(j=0;j<1;j++)
        {
            sum_re=0;
            sum_im=0;
            for(k=0;k<4;k++)
            {
                mult(a1_re[i][k],a1_im[i][k],b1_re[k][j],b1_im[k][j],p_re,p_im);
                sum_re=sum_re+temp_re;
                sum_im=sum_im+temp_im;
            }
            c1_re[i][j]=sum_re;
            c1_im[i][j]=sum_im;
        }
    }
/*
    FILE *fp1,*fp2;
    fp1 = fopen("data.txt","w");
    for( int i = 0 ; i < 4 ; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",c1_re[i][j]);
        }fprintf(fp1,"\n");
    }
    fclose(fp1);
    */
}
void Matrix_mult484(double a1_re[][8],double a1_im[][8],double b1_re[][4],double b1_im[][4],double c1_re[][4],double c1_im[][4])
{
    int i,j,k;
    double sum_re,sum_im;
    double temp_re,temp_im;
    double *p_re;
    double *p_im;
    p_re=&temp_re;
    p_im=&temp_im;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            sum_re=0;
            sum_im=0;
            for(k=0;k<8;k++)
            {
                mult(a1_re[i][k],a1_im[i][k],b1_re[k][j],b1_im[k][j],p_re,p_im);
                sum_re=sum_re+temp_re;
                sum_im=sum_im+temp_im;
            }
            c1_re[i][j]=sum_re;
            c1_im[i][j]=sum_im;
        }
    }
/*
    FILE *fp1,*fp2;
    fp1 = fopen("data.txt","w");
    for( int i = 0 ; i < 4 ; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",c1_re[i][j]);
        }fprintf(fp1,"\n");
    }
    fclose(fp1);
    */
}
void Matrix_mult482(double a1_re[][8],double a1_im[][8],double b1_re[][2],double b1_im[][2],double c1_re[][2],double c1_im[][2])
{
    int i,j,k;
    double sum_re,sum_im;
    double temp_re,temp_im;
    double *p_re;
    double *p_im;
    p_re=&temp_re;
    p_im=&temp_im;
    for(i=0;i<4;i++)
    {
        for(j=0;j<2;j++)
        {
            sum_re=0;
            sum_im=0;
            for(k=0;k<8;k++)
            {
                mult(a1_re[i][k],a1_im[i][k],b1_re[k][j],b1_im[k][j],p_re,p_im);
                sum_re=sum_re+temp_re;
                sum_im=sum_im+temp_im;
            }
            c1_re[i][j]=sum_re;
            c1_im[i][j]=sum_im;
        }
    }
/*
    FILE *fp1,*fp2;
    fp1 = fopen("data.txt","w");
    for( int i = 0 ; i < 4 ; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",c1_re[i][j]);
        }fprintf(fp1,"\n");
    }
    fclose(fp1);
    */
}
void Matrix_mult844(double a1_re[][4],double a1_im[][4],double b1_re[][4],double b1_im[][4],double c1_re[][4],double c1_im[][4])
{
    int i,j,k;
    double sum_re,sum_im;
    double temp_re,temp_im;
    double *p_re;
    double *p_im;
    p_re=&temp_re;
    p_im=&temp_im;
    for(i=0;i<8;i++)
    {
        for(j=0;j<4;j++)
        {
            sum_re=0;
            sum_im=0;
            for(k=0;k<4;k++)
            {
                mult(a1_re[i][k],a1_im[i][k],b1_re[k][j],b1_im[k][j],p_re,p_im);
                sum_re=sum_re+temp_re;
                sum_im=sum_im+temp_im;
            }
            c1_re[i][j]=sum_re;
            c1_im[i][j]=sum_im;
        }
    }
/*
    FILE *fp1,*fp2;
    fp1 = fopen("data.txt","w");
    for( int i = 0 ; i < 4 ; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",c1_re[i][j]);
        }fprintf(fp1,"\n");
    }
    fclose(fp1);
    */
}
void Matrix_mult444(double a1_re[][4],double a1_im[][4],double b1_re[][4],double b1_im[][4],double c1_re[][4],double c1_im[][4])
{
	int i,j,k;
	double sum_re,sum_im;
	double temp_re,temp_im;
	double *p_re;
	double *p_im;
	p_re=&temp_re;
	p_im=&temp_im;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			sum_re=0;
			sum_im=0;
			for(k=0;k<4;k++)
			{
				mult(a1_re[i][k],a1_im[i][k],b1_re[k][j],b1_im[k][j],p_re,p_im);
				sum_re=sum_re+temp_re;
				sum_im=sum_im+temp_im;
			}
			c1_re[i][j]=sum_re;
			c1_im[i][j]=sum_im;
		}
	}
}

void chol_inv(double a1_re[][4],double a1_im[][4],double b1_re[][4],double b1_im[][4])
{
	//初始化
	double d[4]={0}, L_re[4][4]={0};
	double L_im[4][4]={0},d_i[4]={0},L_i_re[4][4]={0},L_i_im[4][4]={0},L_i_re2[4][4]={0},L_i_im2[4][4]={0},D_i_re[4][4]={0},D_i_im[4][4]={0};
	double c_re[4][4]={0},c_im[4][4]={0};
	double *p_re,*p_im,temp_re,temp_im;
	int i,j;
	p_re=&temp_re;
	p_im=&temp_im;
	for(i=0;i<4;i++)
	{
		L_re[i][i]=1;
		L_i_re[i][i]=1;
	}
	
	//cholesky decomposition，Solution of d and L and d_i
	d[0]=a1_re[0][0];
	d_i[0]=1/d[0];
	L_re[1][0]=a1_re[1][0]/d[0];
	L_im[1][0]=a1_im[1][0]/d[0];
	L_re[2][0]=a1_re[2][0]/d[0];
	L_im[2][0]=a1_im[2][0]/d[0];
	L_re[3][0]=a1_re[3][0]/d[0];
	L_im[3][0]=a1_im[3][0]/d[0];

	d[1]=a1_re[1][1]-d[0]*soc(L_re[1][0],L_im[1][0]);
	d_i[1]=1/d[1];
	mult(L_re[2][0],L_im[2][0],L_re[1][0],-L_im[1][0],p_re,p_im);
	L_re[2][1]=(a1_re[2][1]-d[0]*temp_re)/d[1];
	L_im[2][1]=(a1_im[2][1]-d[0]*temp_im)/d[1];
	mult(L_re[3][0],L_im[3][0],L_re[1][0],-L_im[1][0],p_re,p_im);
	L_re[3][1]=(a1_re[3][1]-d[0]*temp_re)/d[1];
	L_im[3][1]=(a1_im[3][1]-d[0]*temp_im)/d[1];

	d[2]=a1_re[2][2]-d[0]*soc(L_re[2][0],L_im[2][0])-d[1]*soc(L_re[2][1],L_im[2][1]);
	d_i[2]=1/d[2];
	mult(L_re[3][0],L_im[3][0],L_re[2][0],-L_im[2][0],p_re,p_im);
	L_re[3][2]=a1_re[3][2]-d[0]*temp_re;
	L_im[3][2]=a1_im[3][2]-d[0]*temp_im;
	mult(L_re[3][1],L_im[3][1],L_re[2][1],-L_im[2][1],p_re,p_im);
	L_re[3][2]=(L_re[3][2]-d[1]*temp_re)/d[2];
	L_im[3][2]=(L_im[3][2]-d[1]*temp_im)/d[2];

	d[3]=a1_re[3][3]-d[0]*soc(L_re[3][0],L_im[3][0])-d[1]*soc(L_re[3][1],L_im[3][1])-d[2]*soc(L_re[3][2],L_im[3][2]);
	d_i[3]=1/d[3];
	


	//L_i
	L_i_re[1][0]=-L_re[1][0];
	L_i_im[1][0]=-L_im[1][0];

	mult(L_re[2][1],L_im[2][1],L_i_re[1][0],L_i_im[1][0],p_re,p_im);
	L_i_re[2][0]=-(temp_re+L_re[2][0]);
	L_i_im[2][0]=-(temp_im+L_im[2][0]);

	mult(L_re[3][1],L_im[3][1],L_i_re[1][0],L_i_im[1][0],p_re,p_im);
	L_i_re[3][0]=L_re[3][0]+temp_re;
	L_i_im[3][0]=L_im[3][0]+temp_im;
	mult(L_re[3][2],L_im[3][2],L_i_re[2][0],L_i_im[2][0],p_re,p_im);
	L_i_re[3][0]=-(L_i_re[3][0]+temp_re);
	L_i_im[3][0]=-(L_i_im[3][0]+temp_im);
	
	L_i_re[2][1]=-L_re[2][1];
	L_i_im[2][1]=-L_im[2][1];

	mult(L_re[3][2],L_im[3][2],L_i_re[2][1],L_i_im[2][1],p_re,p_im);
	L_i_re[3][1]=-(temp_re+L_re[3][1]);
	L_i_im[3][1]=-(temp_im+L_im[3][1]);

	L_i_re[3][2]=-L_re[3][2];
	L_i_im[3][2]=-L_im[3][2];

	//D_i
	for(i=0;i<4;i++)
	{
		D_i_re[i][i]=d_i[i];
	}
	//(L_i)'
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			L_i_re2[i][j]=L_i_re[j][i];
			L_i_im2[i][j]=-L_i_im[j][i];
		}
	}
	//inverse matrix:(L_i)'*D_i*L_i
    Matrix_mult444(L_i_re2,L_i_im2,D_i_re,D_i_im,c_re,c_im);
    Matrix_mult444(c_re,c_im,L_i_re,L_i_im,b1_re,b1_im);
/*
    FILE *fp1,*fp2;
    fp1 = fopen("data.txt","w");
    for( int i = 0 ; i < 4 ; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",b1_re[i][j]);
        }fprintf(fp1,"\n");
    }

    for( int i = 0 ; i < 4 ; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",b1_im[i][j]);
        }fprintf(fp1,"\n");
    }
    fclose(fp1);
    */
} 


void chermitian( int m,int n,COMPLEX *mat48,COMPLEX *mat84_tmp){

    // transform and conj
    //m == 4 n == 8

    for( int i = 0 ; i < m ; i++){
        for( int j = 0 ; j < n ; j++ ){
            (mat84_tmp+j*m+i) ->re  = (mat48+i*n+j)->re;
            (mat84_tmp+j*m+i)->im  = -1 *( (mat48+i*n+j)->im);
            char str[1000];
            sprintf(str,"%d %d re : %lf\n",i,j,(mat84_tmp+j*m+i) ->re);
           // qDebug() << str;
        }
    }
}

void hermitian( int m,int n, double mat48_1_re[][8],double mat48_1_im[][8],
           double mat84_tmp_re[][4],double mat84_tmp_im[][4] ){
    // transform and conj
    //m == 4 n == 8
    for( int i = 0 ; i < m ; i++){
        for( int j = 0 ; j < n ; j++ ){
            mat84_tmp_re[j][i]  = mat48_1_re[i][j];
            mat84_tmp_im[j][i]  = -1 * mat48_1_im[i][j];
        }
    }
/*
    FILE *fp1,*fp2;
    fp1 = fopen("data.txt","w");
    for( int i = 0 ; i < 8 ; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",mat84_tmp_re[i][j]);
        }fprintf(fp1,"\n");
    }
    fclose(fp1);
    */
}

/*
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	int i,j;
	double *p_re,*p_im;
	double a_re[4][4],a_im[4][4],b_re[4][4],b_im[4][4];
	plhs[0]=mxCreateDoubleMatrix(4,4,mxREAL);
	plhs[1]=mxCreateDoubleMatrix(4,4,mxREAL);
	p_re=mxGetPr(prhs[0]);
	p_im=mxGetPr(prhs[1]);
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			{
				a_re[i][j]=p_re[j*4+i];
				a_im[i][j]=p_im[j*4+i];
			}
	}
	
	chol_inv(a_re,a_im,b_re,b_im);
	p_re=mxGetPr(plhs[0]);
	p_im=mxGetPr(plhs[1]);
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			{
				p_re[j*4+i]=b_re[i][j];
				p_im[j*4+i]=b_im[i][j];
			}
	}
}
*/
