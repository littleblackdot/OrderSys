#ifndef CHEFFORM_H
#define CHEFFORM_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QFile>

#include "serverThread.h"
#include "server_tcp.h"
namespace Ui {
class ChefForm;
}

class ChefForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChefForm(QWidget *parent = nullptr);
    QByteArray intToByte(int i);
    int bytesToInt(QByteArray bytes);
    ~ChefForm();
public slots:
    void updateTime();
    void dataUpDate(int tableId);
    void sendOrderstoClients(int tableId);
    void addTableId(int tableId, QTcpSocket* socket);
    void removeSocket(QTcpSocket* socket, int tableid);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ChefForm *ui;
    QTimer *timer;
    server_tcp server;
};

#endif // CHEFFORM_H
