#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QWidget>
#include "activity.h"

class Navigation : public QWidget
{
    Q_OBJECT
public:
    explicit Navigation(QWidget *parent = nullptr);
    explicit Navigation(Activity*activity);
    void closeEvent(QCloseEvent *event);
signals:

public slots:
};

#endif // NAVIGATION_H
