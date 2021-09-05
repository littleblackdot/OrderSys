#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "form1.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_13_clicked();

    void numberButtonfunc(int a);

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
