#ifndef QPSK3_H
#define QPSK3_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glut.h>

namespace Ui {
class QPSK3;
}

class QPSK3 : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit QPSK3(QWidget *parent = 0);
    ~QPSK3();
    

    double *pdata;
    void wallplot();


    void timerEvent(QTimerEvent *event);
    int id1;
    void InputManagement();
    void myDrawCircle(double x, double y, double z, double r);
    void myDrawPoint(double x, double y, double z, double r);

    void myDrawStars();
    int hex2int(char a, char b, char c, char d);
    double char2double(char *str);
    double char2int(char *str);
    int ber();
    void sys_function();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
private:
    GLfloat translate, xRot, yRot, zRot;
private:
    Ui::QPSK3 *ui;
};




#endif // QPSK3_H
