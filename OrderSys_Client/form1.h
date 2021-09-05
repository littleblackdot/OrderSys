#ifndef FORM1_H
#define FORM1_H

#include <QWidget>
#include "message.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <vector>
#define SERVERIPADDR "192.168.124.131"
#define SERVERPORT 11245

using namespace std;

namespace Ui {
class Form1;
}

class Form1 : public QWidget
{
    Q_OBJECT

public:
    explicit Form1(int tableID, QWidget *parent = nullptr);
    ~Form1();
    void updateMenu(MessageFromServer mess);
    void updateOrder(MessageFromServer mess);
    void updateDishesStatus(MessageFromServer mess);
    QByteArray  intToByte(int i);
    int bytesToInt(QByteArray bytes);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Form1 *ui;
    int tableID;
    QTcpSocket *socket;
};

#endif // FORM1_H
