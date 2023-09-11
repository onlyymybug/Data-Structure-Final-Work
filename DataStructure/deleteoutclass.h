#ifndef DELETEOUTCLASS_H
#define DELETEOUTCLASS_H

#include <QWidget>
#include "activity.h"

class DeleteOutclass : public QWidget
{
    Q_OBJECT
public:
    Activity*outclasses;
    int outclassesNum;
    QString username;
    explicit DeleteOutclass(QWidget *parent = nullptr);
    explicit DeleteOutclass(Activity*outclasses,int outclassesNum,QString username);

signals:

public slots:
    void deleteOneOutclass();
    void confirmOutclasses();

};

#endif // DELETEOUTCLASS_H
