#include "filter.h"
#include "logger.h"
//

filter2::filter2(int i, QSharedPointer<comm> _comm)
{
    _log::log("filter2::filter2()");
    this->clear();
    //
    QSharedPointer<QByteArray> _b = QSharedPointer<QByteArray>(
                new QByteArray(_comm->rx(i)));
    //
    if(0<_b->size())
        this->append(_b);
}
