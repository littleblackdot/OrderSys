#ifndef CASHIERFORM_H
#define CASHIERFORM_H

#include <QWidget>

namespace Ui {
class CashierForm;
}

class CashierForm : public QWidget
{
    Q_OBJECT

public:
    explicit CashierForm(QWidget *parent = nullptr);
    ~CashierForm();

private:
    Ui::CashierForm *ui;
};

#endif // CASHIERFORM_H
