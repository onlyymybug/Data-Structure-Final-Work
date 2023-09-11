#include "mymessagebox.h"

MyMessageBox::MyMessageBox()
{

}

void MyMessageBox::setMySize(int inWidth, int inHeight)
{
    this->myWidth=inWidth;
    this->myHeight=inHeight;
}

void MyMessageBox::resizeEvent(QResizeEvent *event)
{
    setFixedSize(myWidth,myHeight);
}

