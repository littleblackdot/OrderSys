#ifndef CASHIERFORM_H
#define CASHIERFORM_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "User.h"
#include "DBHelper.h"
#include <QSqlQuery>

namespace Ui {
class CashierForm;
}

class CashierForm : public QWidget
{
    Q_OBJECT

public:
    explicit CashierForm(User user, QWidget *parent = nullptr);
    ~CashierForm();
    QString createBillId();
public slots:
    void updateTime();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CashierForm *ui;
    User cashier;
    QTimer *timer;
    int curTableId;
};

#endif // CASHIERFORM_H
