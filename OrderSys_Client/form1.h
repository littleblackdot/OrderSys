#ifndef FORM1_H
#define FORM1_H

#include <QWidget>
#include "message.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QFile>
#include <vector>
#define SERVERIPADDR "192.168.200.128"
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
    void sendMessToServer(MessageFromClient mess);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Form1 *ui;
    int tableID;
    QTcpSocket *socket;
};

#endif // FORM1_H
