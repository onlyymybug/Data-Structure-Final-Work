#include "record.h"

extern QString resourcePath;

Record::Record(QObject *parent) : QObject(parent)
{

}

void Record::writeRecord(QString text){
    FILE * fp =fopen((resourcePath+"/record/record.txt").toLatin1().data(),"a+");
    fprintf(fp,"%s\n",text.toStdString().data());
}
