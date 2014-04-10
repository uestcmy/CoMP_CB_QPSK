#include <stdio.h>
#include <math.h>

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


void mult(double x_re,double x_im,double y_re,double y_im,double *p1,double *p2)
{
	double a,b;
	a=x_re*y_re-x_im*y_im;
	b=x_re*y_im+x_im*y_re;
	*p1=a;
	*p2=b;
}

double soc(double x_re,double x_im)
{
	double z;
	z=x_re*x_re+x_im*x_im;
	return(z);
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
