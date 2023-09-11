#ifndef DELETETEMP_H
#define DELETETEMP_H

#include <QWidget>
#include "activity.h"

class DeleteTemp : public QWidget
{
    Q_OBJECT
public:
    Activity*temporarys;
    int temporarysNum;
    QString username;
    explicit DeleteTemp(QWidget *parent = nullptr);
    explicit DeleteTemp(Activity*temporarys,int temporarysNum,QString username);
signals:

public slots:
    void confirmTemp();
    void deleteOneTemp();
};

#endif // DELETETEMP_H
