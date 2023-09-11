#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QCloseEvent>

class Register : public QWidget
{
    Q_OBJECT
public:


    explicit Register(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
signals:

public slots:
};

#endif // REGISTER_H
