#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMessageBox>
#include "DBHelper.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
signals:
    void newUser();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::Form *ui;

};

#endif // FORM_H
