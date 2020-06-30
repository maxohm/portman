#ifndef FILTER_H
#define FILTER_H
//
#include "comm.h"

class filter2 : public QVector<QSharedPointer<QByteArray>>
{
public:
    filter2(int i, QSharedPointer<comm> _comm);
};

#endif //FILTER_H
