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
    ~ChefForm();
public slots:
    void updateTime();
    void dataUpDate();
private:
    Ui::ChefForm *ui;
    QTimer *timer;
    server_tcp server;
};

#endif // CHEFFORM_H
