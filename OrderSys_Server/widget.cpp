#include "widget.h"
#include "ui_widget.h"
#include "DBHelper.h"
#include "User.h"
#include "managerForm.h"
#include "chefForm.h"
#include "cashierForm.h"

#include <QFile>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->setWindowTitle("登陆");
    this->setFixedSize(500, 320);
    this->move(600, 400);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}

void Widget::on_pushButton_clicked()
{
    QString id = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("select * from user where id = %1").arg(id.toInt());
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        qDebug() << str << endl;
        this->close();
    }
    if(!query.next()){
        QMessageBox::warning(this, "提示", "用户不存在");
        return ;
    }
    if(query.value(3) != pwd){
        QMessageBox::warning(this, "提示", "密码错误");
        return ;
    }
    User user(query.value(0).toInt(), (UserType)query.value(1).toInt(), query.value(2).toString());
    switch(user.getUserType()){
        case 0:{
            ManagerForm *form = new ManagerForm;
            form->show();
            this->close();
            break;
        }
        case 1: {
            CashierForm *form = new CashierForm(user);
            form->show();
            this->close();
            break;
        }
        case 2: {
            ChefForm *form = new ChefForm;
            form->show();
            this->close();
            break;
        }
    }

}
