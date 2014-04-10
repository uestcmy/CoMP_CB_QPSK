#include "qpsk3.h"
#include "ui_qpsk3.h"




#include <math.h>
#include <QDebug>
#include <stdio.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QtGui/QApplication>
#include <QFileInfo>
#include <QTextCodec>
#include <QDateTime>



#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include "QDebug"
#include <QtGui/QApplication>
#define LEN 9000
#define LENGTH_OF_OFDM 6144
#define operation

#include "chol_inv_4.cpp"
//#define TEST_SOCKET

socklen_t size_chl2;
int cnt = 0;
sockaddr_in addrSrv_chl1,addrrcv_chl1;
int sockser_chl1;
 double pilot[1200][2] = {0};
 double qam16[500][2] = {0};
char map1200[1200][8];
double data1[1800][2] = {0};//complex number real and image
double data2[1800][2] = {0};
int err = 0;
int bit_cnt = 0;
double new_star[1000][2] = {0};
int cnt_newstar = 0;
int begin2 = 0;
int cnt_pt = 0;
int  cnt_pilot = 0;
QPSK3::QPSK3(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::QPSK3)
{
    ui->setupUi(this);
    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 90;
    zRot += 340;



    InputManagement();
       size_chl2=sizeof(sockaddr_in);
       sockser_chl1=socket(AF_INET,SOCK_DGRAM,0);
       addrSrv_chl1.sin_addr.s_addr=htonl(INADDR_ANY);
       addrSrv_chl1.sin_family=AF_INET;
       addrSrv_chl1.sin_port=htons(7015);//server : receive port number
       bind(sockser_chl1,(sockaddr*)&addrSrv_chl1,sizeof(sockaddr));

       id1 = startTimer(100);


}

QPSK3::~QPSK3()
{
    delete ui;
}

void QPSK3::initializeGL()
{
    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}
void QPSK3::resizeGL(int w, int h)
{
    glViewport(-10, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    //glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, -15.0, 15.0);
     glFrustum (-3* ( GLfloat ) w / ( GLfloat ) h, 3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, 5, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//
void QPSK3::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(0.0, 0.0, translate);// translate is included in <QKeyEvent>
    glTranslatef(0.0, -0.5, 0.3);// translate is included in <QKeyEvent>
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);




    glBegin(GL_QUADS);

    wallplot();
    glEnd();

    /*
    glBegin(GL_LINE);
    glColor4f(0, 0, 0,0.5);//black
    glVertex3f(-0.2,0.5,3);
    glVertex3f(-0.2,0.5,-3);
    glEnd();

    glBegin(GL_LINE);
    glColor4f(1, 0, 0,0.5);//red
    glPointSize(10);
    glVertex3f(0,0.5,0);
    glVertex3f(-0.2,0.5,0);
    glEnd();

    glBegin(GL_POINT);
    glColor4f(1, 0, 0,0.5);
    glPointSize(100);
    glVertex3f(0,0.5,-1);
    glEnd();
*/


    myDrawPoint(-0.2,0.5,0,0.03);
    myDrawStars();
    glColor4f(0,0,0,0.2);


}
void QPSK3::myDrawPoint(double x,double y,double z,double r){//x,y,z, and  radium

        glBegin(GL_QUADS);
        glColor4f(0.8, 0.8, 0,1);//red
        glVertex3f(x,y-r/2,z-r);
        glVertex3f(x,y-r/2,z+r);
        glVertex3f(x,y+r/2,z+r);
        glVertex3f(x,y+r/2,z-r);
        glEnd();
}

void QPSK3::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,2},{-2,-1,2},{-2,-1,-4},{2,-1,-4}};//floor
    double point3[8][3] = {{0,-1,2},{0,-1,-4},{0,2,-4},{0,2,2}};//wall
    double point4[8][3] = {{-0.2,0.5-0.01,2},{-0.2,0.5+0.01,2},{-0.2,0.5+0.01,-4},{-0.2,0.5-0.01,-4}};//shelf
    double point5[8][3] = {{-0.2,2,-1-0.01},{-0.2,-1,-1-0.01},{-0.2,-1,-1+0.01},{-0.2,2,-1+0.01}};//erect


    for( int i = 0 ; i < 4 ; i++ ){
        point5[i][2] += 1;
        point4[i][2] += 1;
        point3[i][2] += 1;
        point2[i+4][2] += 1;
    }
/*
    glColor4f(0, 0, 0,0.2);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
*/
    glColor4f(0, 0, 1,1);
    glVertex3f(point3[0][0], point3[0][1], point3[0][2]);
    glVertex3f(point3[1][0], point3[1][1], point3[1][2]);
    glVertex3f(point3[2][0], point3[2][1], point3[2][2]);
    glVertex3f(point3[3][0], point3[3][1], point3[3][2]);

    glColor4f(0, 0, 0,1);
    glVertex3f(point4[0][0], point4[0][1], point4[0][2]);
    glVertex3f(point4[1][0], point4[1][1], point4[1][2]);
    glVertex3f(point4[2][0], point4[2][1], point4[2][2]);
    glVertex3f(point4[3][0], point4[3][1], point4[3][2]);

    glColor4f(0, 0, 0,1);
    glVertex3f(point5[0][0], point5[0][1], point5[0][2]);
    glVertex3f(point5[1][0], point5[1][1], point5[1][2]);
    glVertex3f(point5[2][0], point5[2][1], point5[2][2]);
    glVertex3f(point5[3][0], point5[3][1], point5[3][2]);

}

void QPSK3::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up :
        xRot += 10;
        break;
    case Qt::Key_Left :
        yRot += 10;
        break;
    case Qt::Key_Right :
        zRot += 10;
        break;
    case Qt::Key_Down :
        translate -= 1;
        if (translate <= -20)
            translate = -1;
        break;
    }
    updateGL();
    QGLWidget::keyPressEvent(event);
}
int first1 = 1;


struct pilotid{
    int id;
    double value;
};

void QPSK3::timerEvent(QTimerEvent *event){
    char buff[LENGTH_OF_OFDM*3+10];
    struct pilotid pilot2[1200];
    for( int i = 0 ; i < 200 ; i++ ){
        pilot2[i].id = i;
        pilot2[i].value = 0;
    }

    recvfrom(sockser_chl1,&buff,LENGTH_OF_OFDM*3+10,0,(struct sockaddr *)&addrrcv_chl1,(socklen_t*)&size_chl2);//port :7005.3


    qDebug() << "Counter is " << cnt++ << endl;

    //qDebug() << buff << endl;

#ifdef operation

    // inverse
    for( int i = 0 ; i < 2400 ; i ++){
       int position = i * 6;
       char tmp;
       //swap
       tmp = buff[position];
       buff[position] = buff[position+3];
       buff[position+3] = tmp;
       //swap
       position ++;
       tmp = buff[position];
       buff[position] = buff[position+3];
       buff[position+3] = tmp;
    }//for
    //qDebug() << buff << endl;

    int position = 12; // avoid the header a0aa 3c20 cccc
    for( int i = 0 ; i < 1200 ; i++){
        for( int j = 0 ; j <8 ;) {
            map1200[i][j++] = buff[position++];
            map1200[i][j++] = buff[position++];
            position++;//avoid the comma
       }//for j
    }//for i
    for( int i = 0 ; i < 1200 ; i++){
        data1[i][0]=hex2int(map1200[i][0],map1200[i][1],map1200[i][2],map1200[i][3]);
        data1[i][1]=hex2int(map1200[i][4],map1200[i][5],map1200[i][6],map1200[i][7]);
       // qDebug() << data1[i][0] << data1[i][1] ;//<<data2[i][0] <<data2[i][1] <<endl;
    }//for i

    sys_function();//data >>   function >> HWS

    double pilotH11[200][2] = {0};
    int cntH11 = 0;
    for( int i = 0 ; i < 1200 ; i++){
        if(i % 6 == 0){//position for the pilot H11
            pilotH11[cntH11][0] = data1[i][0];
            pilotH11[cntH11][1] = data1[i][1];
            pilot2[cntH11].value = sqrt(data1[i][0]*data1[i][0]+data1[i][1]*data1[i][1]);
            cntH11 += 1;
        }//if
    }
    for( int i = 0 ; i < 200 ; i++){
        for( int j = i+1 ; j < 200 ; j++){
            if( pilot2[i].value - pilot2[j].value  < 1e-7 ){
                struct pilotid  tmp = pilot2[i];
                pilot2[i] = pilot2[j];
                pilot2[j] = tmp;
            }
        }
    }
    /*commented by hh
    for( int i = 0 ; i < 100 ; i++ ){
        pilotH11[pilot2[i+100].id ][0] = pilotH11[pilot2[i].id][0];
        pilotH11[pilot2[i+100].id ][1] = pilotH11[pilot2[i].id][1];
        pilot[pilot2[i+100].id][0] = pilot[pilot2[i].id][0];
        pilot[pilot2[i+100].id][1] = pilot[pilot2[i].id][1];

        data1[pilot2[i+100].id*6][0] = data1[pilot2[i].id*6][0];
        data1[pilot2[i+100].id*6][1] = data1[pilot2[i].id*6][1];

        data1[pilot2[i+100].id*6+1][0] = data1[pilot2[i].id*6+1][0];
        data1[pilot2[i+100].id*6+1][1] = data1[pilot2[i].id*6+1][1];

        data1[pilot2[i+100].id*6+2][0] = data1[pilot2[i].id*6+2][0];
        data1[pilot2[i+100].id*6+2][1] = data1[pilot2[i].id*6+2][1];

        data1[pilot2[i+100].id*6+3][0] = data1[pilot2[i].id*6+3][0];
        data1[pilot2[i+100].id*6+3][1] = data1[pilot2[i].id*6+3][1];

        data1[pilot2[i+100].id*6+4][0] = data1[pilot2[i].id*6+4][0];
        data1[pilot2[i+100].id*6+4][1] = data1[pilot2[i].id*6+4][1];

        data1[pilot2[i+100].id*6+5][0] = data1[pilot2[i].id*6+5][0];
        data1[pilot2[i+100].id*6+5][1] = data1[pilot2[i].id*6+5][1];

    }
    */

/*
    for( int i = 0 ; i < 200 ; i++ ){
        qDebug() << pilot2[i].value << pilot2[i].id ;
    }
*/
    double H11[200][2] = {0};
    double absH11[200] = {0};
    double absH11_6[1200][2] = {0};


    //qDebug() << "  ----  ";
    for( int i = 0 ; i < 200 ; i++ ){

        H11[i][0] = (pilotH11[i][0]*pilot[i*6][0]+pilotH11[i][1]*pilot[i*6][1])/(pilot[i*6][0]*pilot[i*6][0]+pilot[i*6][1]*pilot[i*6][1]);
        H11[i][1] = (pilotH11[i][1]*pilot[i*6][0]-pilotH11[i][0]*pilot[i*6][1])/(pilot[i*6][0]*pilot[i*6][0]+pilot[i*6][1]*pilot[i*6][1]);
        //qDebug() << H11[i][0] << H11[i][1]  << "  angle :  "<<atan(H11[i][1]/H11[i][0])<<"pilot"<<pilot[i*6][0]<<"|"<<pilot[i*6][1];

        //qDebug() << "  angle :  "<<atan(H11[i][1]/H11[i][0]);
        absH11[i] = sqrt(H11[i][0]*H11[i][0] + H11[i][1]*H11[i][1]);

    }//for i

    //interp :edited by hh
    for(int i=0;i<200;i++){
        absH11_6[i*6][0] =  H11[i][0];
        absH11_6[i*6 + 1 ][0] =  H11[i][0];
        absH11_6[i*6 + 2 ][0] =  H11[i][0];
        absH11_6[i*6 + 3][0]=  H11[i][0];
        absH11_6[i*6 + 4 ][0] =  H11[i][0];
        absH11_6[i*6 + 5 ][0] =  H11[i][0];

        absH11_6[i*6][1] =  H11[i][1];
        absH11_6[i*6 + 1 ][1] =  H11[i][1];
        absH11_6[i*6 + 2 ][1] =  H11[i][1];
        absH11_6[i*6 + 3][1]=  H11[i][1];
        absH11_6[i*6 + 4 ][1] =  H11[i][1];
        absH11_6[i*6 + 5 ][1] =  H11[i][1];
        absH11_6[i*6 + 6 ][1] =  H11[i][1];

        /*
        absH11_6[i*12][0] =  H11[2*i][0];
        absH11_6[i*12 + 1 ][0] =  H11[2*i][0];
        absH11_6[i*12 + 2 ][0] =  H11[2*i][0];
        absH11_6[i*12 + 3][0]=  H11[2*i][0];
        absH11_6[i*12 + 4 ][0] =  H11[2*i][0];
        absH11_6[i*12 + 5 ][0] =  H11[2*i][0];
        absH11_6[i*12 + 6 ][0] =  H11[2*i][0];
        absH11_6[i*12 + 7 ][0] =  H11[2*i][0];
        absH11_6[i*12 + 8][0]=  H11[2*i][0];
        absH11_6[i*12 + 9 ][0] =  H11[2*i][0];
        absH11_6[i*12 + 10 ][0] =  H11[2*i][0];
        absH11_6[i*12 + 11 ][0] =  H11[2*i][0];

        absH11_6[i*12][1] =  H11[2*i][1];
        absH11_6[i*12 + 1 ][1] =  H11[2*i][1];
        absH11_6[i*12 + 2 ][1] =  H11[2*i][1];
        absH11_6[i*12 + 3][1]=  H11[2*i][1];
        absH11_6[i*12 + 4 ][1] =  H11[2*i][1];
        absH11_6[i*12 + 5 ][1] =  H11[2*i][1];
        absH11_6[i*12 + 6 ][1] =  H11[2*i][1];
        absH11_6[i*12 + 7 ][1] =  H11[2*i][1];
        absH11_6[i*12 + 8][1]=  H11[2*i][1];
        absH11_6[i*12 + 9 ][1] =  H11[2*i][1];
        absH11_6[i*12 + 10 ][1] =  H11[2*i][1];
        absH11_6[i*12 + 11 ][1] =  H11[2*i][1];
        */
    }


    // qDebug() << "  H : ---- ";
    int cntg = 0;
    double guess[1000][2] = {0};

    for( int i = 0 ; i < 600 ; i++){
        if(i%6 != 0){
            // qDebug() << "  H :  "<<absH11_6[i][0];
            guess[cntg][0] = (data1[i][0]*absH11_6[i][0]+data1[i][1]*absH11_6[i][1])/(absH11_6[i][0]*absH11_6[i][0]+absH11_6[i][1]*absH11_6[i][1]);
            //guess[cntg][0] /= 15000;

            guess[cntg][1] = (data1[i][1]*absH11_6[i][0]-data1[i][0]*absH11_6[i][1])/(absH11_6[i][0]*absH11_6[i][0]+absH11_6[i][1]*absH11_6[i][1]);
            //guess[cntg][1]  /= 15000;
            cntg++;
        }//if
    }//for

    for( int i = 600 ; i < 1200 ; i++ ){
        guess[i][0] = guess[i-600][0];
        guess[i][1] = guess[i-600][1];
    }
   // pdata = &guess[0][0];
    pdata = (&new_star[0][0]) ;
   //pdata += cnt_pt;
    cnt_pt+=2;
    if(cnt_pt == 100){
        cnt_pt = 0;
    }


/*
    if(first1 == 1){
         first1 = 0;
         FILE *fp3 = fopen("ofdmdata.txt","w");

        for( int i = 0 ; i <1000 ; i++){
            fprintf(fp3,"%.6lf\t\t%.6lf\t\t%.3lf\t\t%.3lf\n", guess[i][0],guess[i][1]);
        }
        fclose(fp3);
    }//if
*/
    ber();


    updateGL();
    //qDebug()<< "timer event in mygl2 Class!" << endl;
 #endif

}


void QPSK3::sys_function(){
    // (2+i) *(3-i)
    /*
    double re,im;
    mult(2,1,3,-1,&re, &im);
    qDebug() << " re , im : " << re  << im;
*/


    double mat48_1_re[4][8];
    double mat48_1_im[4][8];

    double mat48_2_re[4][8];
    double mat48_2_im[4][8];

    double mat48_tmp_re[4][8];
    double mat48_tmp_im[4][8];

    double mat84_tmp_re[8][4];
    double mat84_tmp_im[8][4];

    double mat44_tmp_re[4][4] = {0};
    double mat44_tmp_im[4][4] = {0};

    double mat44_inv_re[4][4];
    double mat44_inv_im[4][4];

    double w84_re[8][4];
    double w84_im[8][4];

    double hw44_re[4][4];
    double hw44_im[4][4];
/*
    FILE *fp1,*fp2;
    fp2 = fopen("data.txt","r");
     fp1 = fopen("data2out.txt","w");
    for( int i = 0 ; i < 4 ; i++){
        for( int j = 0 ; j < 8 ; j++ ){
            fscanf(fp2,"%lf",&mat48_1_re[i][j]);
        }
    }
    for( int i = 0 ; i < 4 ; i++){
        for( int j = 0 ; j < 8 ; j++ ){
            fscanf(fp2,"%lf",&mat48_1_im[i][j]);
        }
    }
    fclose(fp2);
    */


    for( int t = 0 ; t < 3 ; t++){//time
        for(int f = 0 ; f < 4 ; f ++){//freq
            // get data t1
            for (int i = 0;i<4;i++){
                for(int j=0;j<8;j++){
                    mat48_1_re[i][j]=data1[i*256+j + 64*t + 8*f ][0];
                    mat48_1_im[i][j]=data1[i*256+j + 64*t + 8*f  ][1];
                }
            }
            // get data t2
            for (int i = 0;i<4;i++){
                for(int j=0;j<8;j++){
                    mat48_2_re[i][j]=data1[i*256+j + 64*t+ 64 + 8*f ][0];
                    mat48_2_im[i][j]=data1[i*256+j + 64*t  + 64 + 8*f  ][1];
                }
            }
            hermitian( 4,8,mat48_1_re,mat48_1_im, mat84_tmp_re,mat84_tmp_im );
            Matrix_mult484(mat48_1_re,mat48_1_im, mat84_tmp_re,mat84_tmp_im, mat44_tmp_re,mat44_tmp_im);
            chol_inv(mat44_tmp_re,mat44_tmp_im,mat44_inv_re,mat44_inv_im);
            Matrix_mult844(mat84_tmp_re,mat84_tmp_im, mat44_inv_re,mat44_inv_im, w84_re,w84_im);
            Matrix_mult484(mat48_2_re,mat48_2_im,w84_re,w84_im,hw44_re,hw44_im);
            // jiu xiangpian
            double alpha=0;

            for (int i=0;i<4;i++){
                alpha += 0.25 * atan(hw44_im[i][i]/hw44_re[i][i]);

            }
            double hw2_44_re[4][4];
            double hw2_44_im[4][4];
            for(int i = 0 ; i < 4 ; i++ ){
                for( int j = 0 ; j < 4 ; j++ ){
                    mult(cos(alpha),-sin(alpha),hw44_re[i][j],hw44_im[i][j],&hw2_44_re[i][j],&hw2_44_im[i][j]);
                }
            }
            //get x
            double x_re[4][1];
            double x_im[4][1];
            double y41_re[4][1];
            double y41_im[4][1];
            for( int ip = 0 ; ip < 4 ; ip++ ){
                x_re[ip][0] = pilot[cnt_pilot][0];
                x_im[ip][0] = pilot[cnt_pilot++][1];
                if(cnt_pilot == 1200){
                    cnt_pilot = 0;
                }
            }
            //y = hw*x
            Matrix_mult441(hw2_44_re,hw2_44_im,x_re,x_im,y41_re,y41_im);

            new_star[cnt_newstar][0] = y41_re[2][0];
            new_star[cnt_newstar++][1] = y41_im[2][0];

            if(cnt_newstar == 120){
                cnt_newstar = 0;
            }
        }
    }

   #ifdef onetime
    for (int i = 0;i<4;i++){
        for(int j=0;j<8;j++){
            mat48_1_re[i][j]=data1[i*256+j][0];
            mat48_1_im[i][j]=data1[i*256+j][1];
        }
    }

    for (int i = 0;i<4;i++){
        for(int j=0;j<8;j++){
            mat48_2_re[i][j]=data1[i*256+j+64][0];
            mat48_2_im[i][j]=data1[i*256+j+64][1];
        }
    }
    hermitian( 4,8,mat48_1_re,mat48_1_im,
                    mat84_tmp_re,mat84_tmp_im );

    Matrix_mult484(mat48_1_re,mat48_1_im, mat84_tmp_re,mat84_tmp_im, mat44_tmp_re,mat44_tmp_im);
    chol_inv(mat44_tmp_re,mat44_tmp_im,mat44_inv_re,mat44_inv_im);
    Matrix_mult844(mat84_tmp_re,mat84_tmp_im, mat44_inv_re,mat44_inv_im, w84_re,w84_im);
    Matrix_mult484(mat48_2_re,mat48_2_im,w84_re,w84_im,hw44_re,hw44_im);
    double x_re[4][1];
    double x_im[4][1];
    double y41_re[4][1];
    double y41_im[4][1];

    for( int i = 0 ; i < 4 ; i++ ){
        x_re[i][0] = pilot[i][0];
        x_im[i][0] = pilot[i][1];
    }



    double alpha=0;

    for (int i=0;i<4;i++){
        alpha += 0.25 * atan(hw44_im[i][i]/hw44_re[i][i]);

    }
    double hw2_44_re[4][4];
    double hw2_44_im[4][4];
    for(int i = 0 ; i < 4 ; i++ ){
        for( int j = 0 ; j < 4 ; j++ ){
            mult(cos(alpha),-sin(alpha),hw44_re[i][j],hw44_im[i][j],&hw2_44_re[i][j],&hw2_44_im[i][j]);
        }
    }
    Matrix_mult441(hw2_44_re,hw2_44_im,x_re,x_im,y41_re,y41_im);

/*
    for( int i = 0 ; i < 4; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",hw44_re[i][j]);
        }fprintf(fp1,"\n");
    }
    for( int i = 0 ; i < 4; i++){
        for( int j = 0 ; j < 4 ; j++ ){
            fprintf(fp1,"%lf\t",hw44_im[i][j]);
        }fprintf(fp1,"\n");
    }
    */
    for( int i = 0 ; i < 4; i++){
        qDebug() << hw44_re[i][0] << hw44_re[i][1] << hw44_re[i][2] << hw44_re[i][3];// << mat48_1_re[i][4] << mat48_1_re[i][5] << mat48_1_re[i][6] << mat48_1_re[i][7];
    }qDebug()<<"\n";
    for( int i = 0 ; i < 4; i++){
        qDebug() << hw44_im[i][0] << hw44_im[i][1] << hw44_im[i][2] << hw44_im[i][3] ;//<< hw44_im[i][4] << mat48_2_re[i][5] << mat48_2_re[i][6] << mat48_2_re[i][7];
        }qDebug()<<"\n";

    qDebug() << "y  re is "<< y41_re[0][0] <<  y41_re[1][0] <<  y41_re[2][0] <<  y41_re[3][0] ;
    qDebug() << "y im is "<< y41_im[0][0] <<  y41_im[1][0] <<  y41_im[2][0] <<  y41_im[3][0] ;
    qDebug() << "x  re is "<< pilot[0][0] <<  pilot[1][0] <<  pilot[2][0] <<  pilot[3][0] ;
    qDebug() << "x im is "<< pilot[0][1] <<  pilot[1][1] <<  pilot[2][1] <<  pilot[3][1] ;

    new_star[cnt_newstar][0] = y41_re[1][0];
    new_star[cnt_newstar++][1] = y41_im[1][0];

    new_star[cnt_newstar][0] = y41_re[0][0];
    new_star[cnt_newstar++][1] = y41_im[0][0];
    new_star[cnt_newstar][0] = y41_re[2][0];
    new_star[cnt_newstar++][1] = y41_im[2][0];
    new_star[cnt_newstar][0] = y41_re[3][0];
    new_star[cnt_newstar++][1] = y41_im[3][0];
    if(cnt_newstar == 60){
        cnt_newstar = 0;
    }
#endif
/*
    for( int i = 0 ; i < 4; i++){
        qDebug() << mat48_1_re[i][0] << mat48_1_re[i][1] << mat48_1_re[i][2] << mat48_1_re[i][3] << mat48_1_re[i][4] << mat48_1_re[i][5] << mat48_1_re[i][6] << mat48_1_re[i][7];
    }qDebug()<<"\n";
    for( int i = 0 ; i < 4; i++){
        qDebug() << mat48_2_re[i][0] << mat48_2_re[i][1] << mat48_2_re[i][2] << mat48_2_re[i][3] << mat48_2_re[i][4] << mat48_2_re[i][5] << mat48_2_re[i][6] << mat48_2_re[i][7];
        }qDebug()<<"\n";
*/


   //Matrix_mult484(mat48_1_re,mat48_1_im, mat84_tmp_re,mat84_tmp_im, mat44_tmp_re,mat44_tmp_im);
/*
    for( int i = 0 ; i < 4 ; i++){
         for( int j = 0 ; j < 4 ; j++){
             mat44_tmp_re[i][1] = 1;
         }
    }
    */







}


int QPSK3::hex2int(char a,char b,char c,char d)
{
    /*
      *   eg. ff to 1111 1111
      */

    //qDebug() << "abcd is : " << a << b << c << d << endl;
    int deca = 0,decb = 0,decc = 0,decd = 0;
    if( a >= 'a' && a <= 'f' ){
        deca  = 10 + a -'a';
    }else{
        deca = a - '0';
    }//else

    if( b >= 'a' && b <= 'f' ){
       decb  = 10 + b -'a';
    }else{
        decb = b - '0';
    }//else

    if( c >= 'a' && c <= 'f' ){
        decc  = 10 + c -'a';
    }else{
        decc = c - '0';
    }//else

    if( d >= 'a' && d <= 'f' ){
       decd  = 10 + d -'a';
    }else{
        decd = d - '0';
    }//else

  //qDebug() << "dec abcd is : " << deca << decb << decc << decd << endl;

   int num[16] = {0};
   num[12] = deca % 2;
   deca /= 2;
   num[13] = deca % 2;
   deca /= 2;
   num[14] = deca % 2;
   deca /= 2;
   num[15] = deca % 2;
   deca /= 2;

   num[8] = decb % 2;
   decb /= 2;
   num[9] = decb % 2;
   decb /= 2;
   num[10] = decb % 2;
   decb /= 2;
   num[11] = decb % 2;
   decb /= 2;

   num[4] = decc % 2;
   decc /= 2;
   num[5] = decc % 2;
   decc /= 2;
   num[6] = decc % 2;
   decc /= 2;
   num[7] = decc % 2;
   decc /= 2;

   num[0] = decd % 2;
   decd /= 2;
   num[1] = decd % 2;
   decd /= 2;
   num[2] = decd % 2;
   decd /= 2;
   num[3] = decd % 2;
   decd /= 2;

   int flag = 1;
   if(num[15] == 1){
        flag = -1;
        for( int i = 0 ; i < 15 ; i++ ){
            num[i] = 1 - num[i];
        }
        num[0] ++;
        for( int i = 0 ; i <15 ; i++ ){
            if( num[i] > 1){
                num[i] = 0;
                num[i+1]++;
            }//if
        }
   }
   int res = 0;
   int base = 1;
   for( int i = 0 ; i < 15 ; i++ ){
       res += num[i] *base;
       base *= 2;
   }


   //for i
  // qDebug() << "16 bit is : "  << num[15] << num[14] << num[13] << num[12] << num[11] << num[10] << num[9] << num[8]<< num[7] << num[6]<< num[5] << num[4]<< num[3] << num[2]<< num[1] << num[0] << endl;
   res *= flag;
   //qDebug() << res << endl;
    return res;
}
void QPSK3::InputManagement(){
    QFile file("./Pilot_send_data/pilot_1200_im.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << file.errorString();
        qDebug() << "Last sentence is in QPSK Inputmanagement." << endl;

    }
    //qDebug() << QObject::tr("file text:") << endl << file.readAll();
    //char str[100];
    char str[100];
    for( int i = 0 ; i < 1200 ; i++ ){
        file.readLine(str,100);
        double crr = 0;
        crr = char2int(str);
        //qDebug() << "pilot[ "<< i <<"][0] is :"<<crr;
        pilot[i][0] = crr;
    }
    QFile file1("./Pilot_send_data/pilot_1200_re.txt");
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << file1.errorString();
        qDebug() << "Last sentence is in QPSK Inputmanagement." << endl;

    }
    //qDebug() << QObject::tr("file text:") << endl << file.readAll();
    //char str[100];
    char str2[100];
    for( int i = 0 ; i < 1200 ; i++ ){
        file1.readLine(str2,100);
        double crr = 0;
        crr = char2int(str2);
        //qDebug() << "pilot[ "<< i <<"][0] is :"<<crr;
        pilot[i][1] = crr;
    }

}

double QPSK3::char2double(char *str){
    double  ans = 0;

    if(str[0] == '-'){
        if(str[1] == '3')
            return -3/sqrt(10);
        else if(str[1] == '1')
            return -1/sqrt(10);
    }
    else{
        if(str[0] == '3')
            return 3/sqrt(10);
        else if(str[0] == '1')
            return 1/sqrt(10);
    }
    return ans;
}
double QPSK3::char2int(char *str){
    /*
     *  eg. 2.789 -2.789
     */
    double ans = 0;

    if(str[0] == '-'){
        return -1.0/sqrt(2);
    }
    else{
       return  1.0/sqrt(2);
    }
    return ans;
}

void QPSK3::myDrawStars(){

    for( int i = 0  ; i < 1000 ; i++ ){
        double z = (*(pdata+i*2+0));
        double y = *(pdata+i*2+1);


        //qDebug()<< "in my DrawStars, x ,y is " << z<<" , "<<y<<endl;
        myDrawPoint(-0.2,y+0.5,z*2,0.02);
        //qDebug() <<"z :" << z <<"y :" << y ;
    }


}
int QPSK3::ber(){

    //qDebug() << "start";
    for( int i = 0 ; i < 500 ; i++ ){
        double y = (*(pdata+i*2+0));
        double z = *(pdata+i*2+1);
        double diff = sqrt( (z-qam16[i][0])*(z-qam16[i][0])+(y - qam16[i][1])*(y - qam16[i][1])  );

        //qDebug() << z << qam16[i][0] << "  |  " <<y<<qam16[i][1]<<"|"<<(diff)<<"|"<<1/sqrt(10);
        if(diff> 1/sqrt(10)){
              err++;
        }
        bit_cnt++;

        if(bit_cnt == 20000){
            qDebug() << "BER :" <<err/20000.0 ;
             err = 0;
             bit_cnt = 0;
        }
       // qDebug()<< "in my DrawStars, x ,y is " << z<<" , "<<y<<endl;

    }
}
