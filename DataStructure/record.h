#ifndef RECORD_H
#define RECORD_H

#include <QObject>

class Record : public QObject
{
    Q_OBJECT
public:
    explicit Record(QObject *parent = nullptr);
    void writeRecord(QString text);
signals:

public slots:
};

#endif // RECORD_H
