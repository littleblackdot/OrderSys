#ifndef ADDDISHFORM_H
#define ADDDISHFORM_H

#include <QWidget>

namespace Ui {
class addDishForm;
}

class addDishForm : public QWidget
{
    Q_OBJECT

public:
    explicit addDishForm(QWidget *parent = nullptr);
    ~addDishForm();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
signals:
    void newDish();
private:
    Ui::addDishForm *ui;
};

#endif // ADDDISHFORM_H
