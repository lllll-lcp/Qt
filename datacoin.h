#ifndef DATACOIN_H
#define DATACOIN_H

#include <QObject>
#include <QMap>
#include <QVector>

class dataCoin : public QObject
{
    Q_OBJECT
public:
    explicit dataCoin(QObject *parent = 0);

public:
    QMap<int,QVector<QVector<int>>>mData;

signals:

public slots:
};

#endif // DATACOIN_H
