#ifndef MANAGERFORM_H
#define MANAGERFORM_H

#include <QWidget>

namespace Ui {
class ManagerForm;
}

class ManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerForm(QWidget *parent = nullptr);
    ~ManagerForm();

private:
    Ui::ManagerForm *ui;
};

#endif // MANAGERFORM_H
