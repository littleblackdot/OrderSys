#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(570, 430);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_3_clicked()
{
    numberButtonfunc(3);
}


void Widget::on_pushButton_clicked()
{
   numberButtonfunc(1);
}

void Widget::on_pushButton_2_clicked()
{
    numberButtonfunc(2);
}

void Widget::on_pushButton_8_clicked()
{
    numberButtonfunc(8);
}

void Widget::on_pushButton_4_clicked()
{
    numberButtonfunc(4);
}

void Widget::on_pushButton_5_clicked()
{
    numberButtonfunc(5);
}

void Widget::on_pushButton_6_clicked()
{
    numberButtonfunc(6);
}

void Widget::on_pushButton_7_clicked()
{
    numberButtonfunc(7);
}

void Widget::on_pushButton_9_clicked()
{
    numberButtonfunc(9);
}

void Widget::on_pushButton_13_clicked()
{
    numberButtonfunc(0);
}

void Widget::numberButtonfunc(int a)
{
    if(ui->lineEdit->text() == ""){
        ui->lineEdit->setText(QString("%1").arg(a));
        return ;
    }
    double tableID = ui->lineEdit->text().toDouble();
    QString id;
    if( 0 == tableID){
        id = QString("%1").arg(a);
    }else{
        id = ui->lineEdit->text().append(QString("%1").arg(a));
    }
    ui->lineEdit->setText(id);
}

void Widget::on_pushButton_12_clicked()
{
    ui->lineEdit->setText("");
}

void Widget::on_pushButton_10_clicked()
{
    int tableID = ui->lineEdit->text().toInt();
    Form1 *form = new Form1(tableID);
    form->show();
}
