#ifndef TERMIN_H
#define TERMIN_H
//
#include <QMainWindow>
//
#include "../libcomm/libcomm.h"

namespace Ui {
class termin;
}

class termin : public QMainWindow
{
    Q_OBJECT

public:
    explicit termin(QWidget *parent = 0);
    ~termin();

private:
    Ui::termin *ui;
    //
    QVector<QSharedPointer<QByteArray>> buff;
    QSharedPointer<comm> comm1;
    //
    QAction* sendAction;

private slots:
    void poll();

};

#endif // TERMIN_H
