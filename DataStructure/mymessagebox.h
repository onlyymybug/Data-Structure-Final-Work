#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H
#include <QMessageBox>

class MyMessageBox : public QMessageBox
{
public:
    int myWidth=300;
    int myHeight=200;

    MyMessageBox();
    void setMySize(int inWidth,int inHeight);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    //void buttonClicked(QAbstractButton *button);
signals:

protected:
};

#endif // MYMESSAGEBOX_H
