#ifndef PWDCHANGEFORM_H
#define PWDCHANGEFORM_H

#include <QWidget>
namespace Ui {
class pwdChangeForm;
}

class pwdChangeForm : public QWidget
{
    Q_OBJECT

public:
    explicit pwdChangeForm(int userid, QWidget *parent = nullptr);
    ~pwdChangeForm();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::pwdChangeForm *ui;
    int userId;
};

#endif // PWDCHANGEFORM_H
