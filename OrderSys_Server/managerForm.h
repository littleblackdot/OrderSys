#ifndef MANAGERFORM_H
#define MANAGERFORM_H

#include <QWidget>
#include "DBHelper.h"
#include "form.h"
#include "pwdchangeform.h"
#include "typechangeform.h"
#include "adddishform.h"
namespace Ui {
class ManagerForm;
}

class ManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerForm(QWidget *parent = nullptr);
    ~ManagerForm();
    void showUsers();
    void showMenu();
    void showBills(int option, QString billId = "");
private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();
    void updateUserTable();
    void updateMenuTable();

private:
    Ui::ManagerForm *ui;
};

#endif // MANAGERFORM_H
