#include "pwdchangeform.h"
#include "ui_pwdchangeform.h"
#include "DBHelper.h"
#include <QMessageBox>
#include <QFile>
pwdChangeForm::pwdChangeForm(int userId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pwdChangeForm),
    userId(userId)
{
    QFile qss(":/white.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    ui->setupUi(this);
    this->setWindowTitle("密码修改");
    this->setFixedSize(315, 275);
}

pwdChangeForm::~pwdChangeForm()
{
    delete ui;
}

void pwdChangeForm::on_pushButton_clicked()
{
    QString pwd_old = ui->lineEdit->text();
    if(pwd_old == ""){
        return;
    }
    QString pwd_new = ui->lineEdit_2->text();
    if(pwd_new != ui->lineEdit_3->text()){
        QMessageBox::information(this, QString("提示"), QString("密码不一致"), QMessageBox::Cancel, QMessageBox::Cancel);
        return;
    }
    DBHelper helper;
    QSqlQuery query(helper.getDB());
    QString sql = QString("select passwd from user where id = %1").arg(userId);
    bool ret = query.exec(sql);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        QMessageBox::warning(this, "提示", str);
    }
    if(query.next()){
        if(pwd_old != query.value(0).toString()){
            QMessageBox::information(this, QString("提示"), QString("原密码错误"), QMessageBox::Cancel, QMessageBox::Cancel);
            return;
        }
    }
    QString sql2 = QString("update user set passwd = '%1' where id = %2").arg(pwd_new).arg(userId);
    ret = query.exec(sql2);
    if(!ret){
        QSqlError err = query.lastError();   //得到最近一次的错误信息
        QString str = QString("错误信息:%1, %2").arg(err.driverText()).arg(err.databaseText());
        QMessageBox::warning(this, "提示", str);
        return ;
    }
    QMessageBox::information(this, QString("提示"), QString("密码修改成功"), QMessageBox::Cancel, QMessageBox::Cancel);
}

void pwdChangeForm::on_pushButton_2_clicked()
{
    //重置
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
}
