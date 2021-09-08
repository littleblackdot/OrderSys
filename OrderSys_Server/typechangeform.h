#ifndef TYPECHANGEFORM_H
#define TYPECHANGEFORM_H

#include <QWidget>

namespace Ui {
class typeChangeForm;
}

class typeChangeForm : public QWidget
{
    Q_OBJECT

public:
    explicit typeChangeForm(int userId, QWidget *parent = nullptr);
    ~typeChangeForm();

private slots:
    void on_pushButton_clicked();
signals:
    void userChange();
private:
    Ui::typeChangeForm *ui;
    int userId;
};

#endif // TYPECHANGEFORM_H
